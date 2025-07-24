#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <iomanip>

// Include ONNX Runtime C++ API
#include <onnxruntime_cxx_api.h>

// Structure to hold input features
struct PhoneFeatures {
    float battery_health;
    int purchase_year;
    int battery_cycles;
    float damage_percent;
    std::string iphone_version;
};

// Function to run inference using the ONNX model
float predict_iphone_price(
    Ort::Session& session,
    const PhoneFeatures& features,
    Ort::AllocatorWithDefaultOptions& allocator)
{
    // Input names (must match model)
    std::vector<const char*> input_node_names = {
        "battery_health",
        "purchase_year",
        "battery_cycles",
        "damage_percent",
        "iphone_version"
    };

    std::vector<Ort::Value> input_tensors;
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    std::vector<int64_t> shape = {1, 1};

    // Numeric inputs
    std::vector<float> battery_health_data = {features.battery_health};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, battery_health_data.data(), battery_health_data.size(),
        shape.data(), shape.size()));

    std::vector<float> purchase_year_data = {static_cast<float>(features.purchase_year)};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, purchase_year_data.data(), purchase_year_data.size(),
        shape.data(), shape.size()));

    std::vector<float> battery_cycles_data = {static_cast<float>(features.battery_cycles)};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, battery_cycles_data.data(), battery_cycles_data.size(),
        shape.data(), shape.size()));

    std::vector<float> damage_percent_data = {features.damage_percent};
    input_tensors.push_back(Ort::Value::CreateTensor<float>(
        memory_info, damage_percent_data.data(), damage_percent_data.size(),
        shape.data(), shape.size()));

    // String input (iphone_version)
    std::vector<int64_t> iphone_version_shape = {1, 1};
    Ort::Value iphone_version_tensor = Ort::Value::CreateTensor(
        allocator,
        iphone_version_shape.data(),
        iphone_version_shape.size(),
        ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING
    );

    std::vector<const char*> c_str_iphone_version = {features.iphone_version.c_str()};
    iphone_version_tensor.FillStringTensor(c_str_iphone_version.data(), c_str_iphone_version.size());

    input_tensors.push_back(std::move(iphone_version_tensor));

    // Output node names using ONNX Runtime 1.16+ style
    size_t output_count = session.GetOutputCount();
    std::vector<const char*> output_node_names;

    for (size_t i = 0; i < output_count; ++i) {
        char* output_name = nullptr;
        Ort::GetApi().SessionGetOutputName(session, i, allocator, &output_name);
        output_node_names.push_back(output_name);
    }

    // Run inference
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

    if (output_tensors.empty()) {
        std::cerr << "Error: No output tensors received." << std::endl;
        return -1.0f;
    }

    float predicted_price = -1.0f;
    if (output_tensors[0].IsTensor()) {
        const float* output_data = output_tensors[0].GetTensorData<float>();
        if (output_data) {
            predicted_price = output_data[0];
        } else {
            std::cerr << "Error: Could not get tensor data from output." << std::endl;
        }
    } else {
        std::cerr << "Error: Output is not a tensor." << std::endl;
    }

    return predicted_price;
}

int main() {
    // Initialize ONNX Runtime
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "iphone_price_predictor");

    // Session options
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(ORT_ENABLE_EXTENDED);

    // Load model
    const char* model_path = "iphone_price_predictor.onnx";
    Ort::Session session(env, model_path, session_options);

    // Allocator
    Ort::AllocatorWithDefaultOptions allocator;

    // First input
    std::cout << "Enter iPhone features to predict resale price:\n";

    PhoneFeatures user_input;
    std::cout << "Battery health (0-100): ";
    std::cin >> user_input.battery_health;

    std::cout << "Purchase year (e.g. 2021): ";
    std::cin >> user_input.purchase_year;

    std::cout << "Battery cycles: ";
    std::cin >> user_input.battery_cycles;

    std::cout << "Damage percent (0-1, e.g. 0.2): ";
    std::cin >> user_input.damage_percent;

    std::cin.ignore(); // flush newline
    std::cout << "iPhone version (e.g. iPhone 13 Pro): ";
    std::getline(std::cin, user_input.iphone_version);
    float price = predict_iphone_price(session, user_input, allocator);
    if (price != -1.0f) {
        std::cout << "Predicted price for " << user_input.iphone_version << ": $"
                  << std::fixed << std::setprecision(2) << price << std::endl;
    } else {
        std::cout << "Prediction failed." << std::endl;
    }
    return 0;
}
