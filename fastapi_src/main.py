from fastapi import FastAPI
from pydantic import BaseModel
import numpy as np
import onnxruntime as ort

app = FastAPI()

# Load ONNX model
onnx_session = ort.InferenceSession("../models/iphone_price_predictor.onnx")

# Input schema
class PhoneFeatures(BaseModel):
    battery_health: float
    purchase_year: int
    battery_cycles: int
    damage_percent: float
    iphone_version_code: float  # Already mapped to numeric

# Helper to transform input into a single tensor
def to_onnx_input(data: PhoneFeatures):
    input_array = np.array([[
        data.battery_health,
        data.purchase_year,
        data.battery_cycles,
        data.damage_percent,
        data.iphone_version_code,
    ]], dtype=np.float32)
    
    return {"input": input_array}  # "input" must match ONNX input name

# Predict endpoint
@app.post("/predict")
def predict_price_onnx(data: PhoneFeatures):
    inputs = to_onnx_input(data)
    result = onnx_session.run(None, inputs)
    predicted_price = float(result[0][0])
    return {"predicted_price": round(predicted_price, 2)}