const express = require("express");
const ort = require("onnxruntime-node");
const bodyParser = require("body-parser");

const app = express();
const PORT = 3000;

app.use(bodyParser.json());

let session;
ort.InferenceSession.create("../models/iphone_price_predictor.onnx").then((s) => {
  session = s;
  console.log("ONNX model loaded.");
});

app.post("/predict", async (req, res) => {
  if (!session) {
    return res.status(503).send("Model not loaded yet");
  }

  try {
    const input = req.body;

    // Prepare single float32 tensor with shape [1, 5]
    const inputTensor = new ort.Tensor(
      "float32",
      Float32Array.from([
        input.battery_health,
        input.purchase_year,
        input.battery_cycles,
        input.damage_percent,
        input.iphone_version_code
      ]),
      [1, 5]
    );

    const feeds = { input: inputTensor };

    const results = await session.run(feeds);

    const outputKey = Object.keys(results)[0];
    const predictedPrice = results[outputKey].data[0];

    res.json({ predicted_price: predictedPrice });
  } catch (err) {
    console.error("Prediction failed:", err.message);
    res.status(500).send("Prediction failed: " + err.message);
  }
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});