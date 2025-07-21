const express = require("express");
const ort = require("onnxruntime-node");
const bodyParser = require("body-parser");

const app = express();
const PORT = 3000;

app.use(bodyParser.json());

// Pre-load ONNX session
let session;
ort.InferenceSession.create("../models/iphone_price_predictor.onnx").then((s) => {
  session = s;
  console.log("ONNX model loaded.");
});

// iPhone version encoding (ordinal)
const iphoneVersions = [
  "iPhone 11", "iPhone 11 Pro", "iPhone 12", "iPhone 12 Pro",
  "iPhone 13", "iPhone 13 Pro", "iPhone 14", "iPhone 14 Pro",
  "iPhone 15", "iPhone 15 Pro", "iPhone 16", "iPhone 16 Pro"
];

const encodeVersion = (version) => {
  const idx = iphoneVersions.indexOf(version);
  if (idx === -1) throw new Error("Invalid iPhone version");
  return idx;
};

app.post("/predict", async (req, res) => {
  if (!session) {
    return res.status(503).send("Model not loaded yet");
  }

  try {
    const input = req.body;

    // Build individual input tensors matching model expectations
    const feeds = {
      battery_health: new ort.Tensor("float32", Float32Array.from([input.battery_health]), [1, 1]),
      purchase_year: new ort.Tensor("float32", Float32Array.from([input.purchase_year]), [1, 1]),
      battery_cycles: new ort.Tensor("float32", Float32Array.from([input.battery_cycles]), [1, 1]),
      damage_percent: new ort.Tensor("float32", Float32Array.from([input.damage_percent]), [1, 1]),
      iphone_version: new ort.Tensor("string", [iphoneVersions[encodeVersion(input.iphone_version)]], [1, 1])
    };

    const results = await session.run(feeds);

    // Get first output (assuming single output)
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
