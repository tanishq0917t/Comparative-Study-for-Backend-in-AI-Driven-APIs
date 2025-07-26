package com.example.demo.controller;

import ai.onnxruntime.*;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.io.InputStream;
import java.util.*;

@RestController
public class PredictController {

    private final OrtEnvironment env;
    private final OrtSession session;

    public PredictController() throws OrtException, IOException {
        env = OrtEnvironment.getEnvironment();

        // Load model.onnx from resources
        InputStream modelStream = getClass().getClassLoader().getResourceAsStream("model.onnx");
        if (modelStream == null) {
            throw new IOException("model.onnx not found in resources directory.");
        }

        byte[] modelBytes = modelStream.readAllBytes();
        OrtSession.SessionOptions options = new OrtSession.SessionOptions();
        session = env.createSession(modelBytes, options);
    }

    @PostMapping("/predict")
    public Map<String, Object> predict(@RequestBody Map<String, Float> input) throws OrtException {
        // Extract and validate input fields
        float batteryHealth = Objects.requireNonNull(input.get("battery_health"), "Missing battery_health");
        float purchaseYear = Objects.requireNonNull(input.get("purchase_year"), "Missing purchase_year");
        float batteryCycles = Objects.requireNonNull(input.get("battery_cycles"), "Missing battery_cycles");
        float damagePercent = Objects.requireNonNull(input.get("damage_percent"), "Missing damage_percent");
        float iphoneVersion = Objects.requireNonNull(input.get("iphone_version_code"), "Missing iphone_version");

        float[] inputData = new float[]{
            batteryHealth,
            purchaseYear,
            batteryCycles,
            damagePercent,
            iphoneVersion
        };

        // Wrap input in a tensor
        try (OnnxTensor inputTensor = OnnxTensor.createTensor(env, new float[][]{inputData});
             OrtSession.Result result = session.run(Collections.singletonMap("input", inputTensor))) {

            float[][] output = (float[][]) result.get(0).getValue();
            Map<String, Object> response = new HashMap<>();
            response.put("price", output[0][0]);
            return response;
        }
    }
}
