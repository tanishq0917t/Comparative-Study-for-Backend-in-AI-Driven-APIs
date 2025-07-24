#include "crow_all.h"  // Crow single-header
#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Struct to represent iPhone features
struct PhoneFeatures {
    float battery_health;
    int purchase_year;
    int battery_cycles;
    float damage_percent;
    std::string iphone_version;
};

// Prediction function
float predict_iphone_price(
    Ort::Session& session,
    const PhoneFeatures& features,
    Ort::AllocatorWithDefaultOptions& allocator)
{
    std::vector<const char*> input_node_names = {
        "battery_health", "purchase_year", "battery_cycles", "damage_percent", "iphone_version"
    };

    std::vector<Ort::Value> input_tensors;
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    std::vector<int64_t> shape = {1, 1};

    std::vector<float> battery_health_data = {features.battery_health};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, battery_health_data.data(), battery_health_data.size(), shape.data(), shape.size()));

    std::vector<float> purchase_year_data = {static_cast<float>(features.purchase_year)};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, purchase_year_data.data(), purchase_year_data.size(), shape.data(), shape.size()));

    std::vector<float> battery_cycles_data = {static_cast<float>(features.battery_cycles)};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, battery_cycles_data.data(), battery_cycles_data.size(), shape.data(), shape.size()));

    std::vector<float> damage_percent_data = {features.damage_percent};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, damage_percent_data.data(), damage_percent_data.size(), shape.data(), shape.size()));

    std::vector<int64_t> iphone_version_shape = {1, 1};
    Ort::Value iphone_version_tensor = Ort::Value::CreateTensor(
        allocator, iphone_version_shape.data(), iphone_version_shape.size(), ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING);

    std::vector<const char*> c_str_iphone_version = {features.iphone_version.c_str()};
    iphone_version_tensor.FillStringTensor(c_str_iphone_version.data(), c_str_iphone_version.size());
    input_tensors.push_back(std::move(iphone_version_tensor));

    size_t output_count = session.GetOutputCount();
    std::vector<const char*> output_node_names;

    for (size_t i = 0; i < output_count; ++i) {
        char* output_name = nullptr;
        Ort::GetApi().SessionGetOutputName(session, i, allocator, &output_name);
        output_node_names.push_back(output_name);
    }

    std::vector<Ort::Value> output_tensors;
    try {
        output_tensors = session.Run(
            Ort::RunOptions{nullptr},
            input_node_names.data(),
            input_tensors.data(),
            input_tensors.size(),
            output_node_names.data(),
            output_node_names.size()
        );
    } catch (const Ort::Exception& e) {
        std::cerr << "ONNX Runtime inference failed: " << e.what() << std::endl;
        for (auto name : output_node_names)
            allocator.Free((void*)name);
        return -1.0f;
    }

    for (auto name : output_node_names)
        allocator.Free((void*)name);

    if (output_tensors.empty()) return -1.0f;

    const float* output_data = output_tensors[0].GetTensorData<float>();
    return output_data ? output_data[0] : -1.0f;
}

int main() {
    // Init ONNX
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "iphone_price_predictor");
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(ORT_ENABLE_EXTENDED);
    Ort::Session session(env, "iphone_price_predictor.onnx", session_options);
    Ort::AllocatorWithDefaultOptions allocator;

    crow::SimpleApp app;

    // POST /predict endpoint
    CROW_ROUTE(app, "/predict").methods("POST"_method)([&](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        try {
            PhoneFeatures features;
            features.battery_health = body["battery_health"].i();  // If coming as int
            features.purchase_year = body["purchase_year"].i();
            features.battery_cycles = body["battery_cycles"].i();
            features.damage_percent = body["damage_percent"].i();  // Or .d() if float
            features.iphone_version = body["iphone_version"].s();

            float price = predict_iphone_price(session, features, allocator);
            if (price < 0)
                return crow::response(500, "Prediction failed");

            crow::json::wvalue res;
            res["iphone_version"] = features.iphone_version;
            res["predicted_price"] = price;
            return crow::response(res);
        } catch (...) {
            return crow::response(500, "Unexpected error");
        }
    });

    std::cout << "Server running on http://localhost:8080\n";
    app.port(8080).multithreaded().run();

    return 0;
}

