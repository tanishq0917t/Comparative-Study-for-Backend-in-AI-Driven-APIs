import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.pipeline import Pipeline
from sklearn.metrics import root_mean_squared_error
import joblib
import numpy as np

# For ONNX export
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType

# Step 1: Load Data
df = pd.read_csv("dataset/iphone_prices_dataset.csv")

# Step 2: Define Features and Target
X = df.drop("price", axis=1)
y = df["price"]

# Convert to NumPy for ONNX compatibility (single tensor input)
X = X.values

# Step 3: Define Model Pipeline (no preprocessing needed)
pipeline = Pipeline([
    ("regressor", RandomForestRegressor(n_estimators=100, random_state=42))
])

# Step 4: Train-Test Split and Train
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
pipeline.fit(X_train, y_train)

# Step 5: Evaluate
y_pred = pipeline.predict(X_test)
rmse = root_mean_squared_error(y_test, y_pred)
print(f"✅ Root Mean Squared Error (RMSE): {rmse:.2f}")

# Step 6: Save Sklearn model
joblib.dump(pipeline, "iphone_price_predictor.pkl")

# Step 7: Export to ONNX (use single input tensor with shape [None, 5])
initial_type = [("input", FloatTensorType([None, 5]))]
onnx_model = convert_sklearn(pipeline, initial_types=initial_type)

with open("iphone_price_predictor.onnx", "wb") as f:
    f.write(onnx_model.SerializeToString())

print("✅ Model exported to ONNX successfully!")