from fastapi import FastAPI
from pydantic import BaseModel
import numpy as np
import onnxruntime as ort

app = FastAPI()

# Load models
onnx_session = ort.InferenceSession("../models/iphone_price_predictor.onnx")

# Input schema
class PhoneFeatures(BaseModel):
    battery_health: float
    purchase_year: int
    battery_cycles: int
    damage_percent: float
    iphone_version: str

# Helper for ONNX input transformation
def to_onnx_input(data: PhoneFeatures):
    return {
        "battery_health": np.array([[data.battery_health]], dtype=np.float32),
        "purchase_year": np.array([[data.purchase_year]], dtype=np.float32),
        "battery_cycles": np.array([[data.battery_cycles]], dtype=np.float32),
        "damage_percent": np.array([[data.damage_percent]], dtype=np.float32),
        "iphone_version": np.array([[data.iphone_version]], dtype=str),
    }

# Endpoint using ONNX model
@app.post("/predict")
def predict_price_onnx(data: PhoneFeatures):
    inputs = to_onnx_input(data)
    print(type(inputs["iphone_version"]))
    result = onnx_session.run(None, inputs)
    print(result)
    predicted_price = float(result[0][0][0])
    return {"predicted_price": round(predicted_price, 2)}

