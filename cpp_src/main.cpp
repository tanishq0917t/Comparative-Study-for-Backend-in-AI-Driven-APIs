#include <crow_all.h>
#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>
#include <stdexcept>

// Struct to hold the input features
struct PhoneFeatures {
    float battery_health;
    float purchase_year;
    float battery_cycles;
    float damage_percent;
    float iphone_version_code;
};

// Function to get dynamic output name
std::string get_output_name(Ort::Session& session, Ort::AllocatorWithDefaultOptions& allocator) {
    Ort::AllocatedStringPtr name_ptr = session.GetOutputNameAllocated(0, allocator);
    return std::string(name_ptr.get());
}

// Prediction logic
float predict_iphone_price(Ort::Session& session, const PhoneFeatures& features, const std::string& output_name) {
    Ort::AllocatorWithDefaultOptions allocator;

    const char* input_names[] = {"input"};
    const char* output_names[] = {output_name.c_str()};
    std::vector<int64_t> input_shape = {1, 5};

    std::vector<float> input_tensor_values = {
        features.battery_health,
        features.purchase_year,
        features.battery_cycles,
        features.damage_percent,
        features.iphone_version_code
    };

    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(
        OrtAllocatorType::OrtArenaAllocator,
        OrtMemType::OrtMemTypeDefault
    );

    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info,
        input_tensor_values.data(),
        input_tensor_values.size(),
        input_shape.data(),
        input_shape.size()
    );

    auto output_tensors = session.Run(
        Ort::RunOptions{nullptr},
        input_names,
        &input_tensor,
        1,
        output_names,
        1
    );

    float* float_array = output_tensors[0].GetTensorMutableData<float>();
    return float_array[0];
}

int main() {
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "predictor");
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);

    Ort::Session session(env, "iphone_price_predictor.onnx", session_options);
    Ort::AllocatorWithDefaultOptions allocator;
    std::string output_name = get_output_name(session, allocator);

    crow::SimpleApp app;

    CROW_ROUTE(app, "/predict").methods("POST"_method)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        try {
            PhoneFeatures features;
            features.battery_health = body["battery_health"].d();
            features.purchase_year = body["purchase_year"].d();
            features.battery_cycles = body["battery_cycles"].d();
            features.damage_percent = body["damage_percent"].d();
            features.iphone_version_code = body["iphone_version_code"].d();

            float price = predict_iphone_price(session, features, output_name);

            crow::json::wvalue res;
            res["predicted_price"] = price;
            return crow::response(res);
        } catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << std::endl;
            return crow::response(500, std::string("Internal Server Error: ") + e.what());
        } catch (...) {
            std::cerr << "Unknown exception occurred." << std::endl;
            return crow::response(500, "Unknown internal server error");
        }
    });

    std::cout << "Server running at http://localhost:8080\n";
    app.port(8080).multithreaded().run();
}