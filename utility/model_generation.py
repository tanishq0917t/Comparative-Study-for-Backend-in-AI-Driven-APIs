import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.preprocessing import OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.metrics import root_mean_squared_error
import joblib

# For ONNX
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType, StringTensorType

# Step 1: Load Data
df = pd.read_csv("dataset/iphone_prices_dataset.csv")

# Step 2: Define Features and Target
X = df.drop("price", axis=1)
y = df["price"]

# Step 3: Preprocessing
categorical_features = ["iphone_version"]
numeric_features = ["battery_health", "purchase_year", "battery_cycles", "damage_percent"]

preprocessor = ColumnTransformer(
    transformers=[
        ("cat", OneHotEncoder(handle_unknown="ignore"), categorical_features),
    ],
    remainder="passthrough"  # numeric features will be passed as-is
)

# Step 4: Pipeline
pipeline = Pipeline([
    ("preprocessor", preprocessor),
    ("regressor", RandomForestRegressor(n_estimators=100, random_state=42))
])

# Step 5: Train-Test Split and Train
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
pipeline.fit(X_train, y_train)

# Step 6: Evaluate
y_pred = pipeline.predict(X_test)
rmse = root_mean_squared_error(y_test, y_pred)
print(f"Root Mean Squared Error (RMSE): {rmse:.2f}")

# Step 7: Save Sklearn model (optional)
joblib.dump(pipeline, "iphone_price_predictor.pkl")

# Step 8: Export to ONNX
# Define input types for ONNX conversion
initial_type = [
    ("battery_health", FloatTensorType([None, 1])),
    ("purchase_year", FloatTensorType([None, 1])),
    ("battery_cycles", FloatTensorType([None, 1])),
    ("damage_percent", FloatTensorType([None, 1])),
    ("iphone_version", StringTensorType([None, 1])),
]

onnx_model = convert_sklearn(pipeline, initial_types=initial_type)
with open("iphone_price_predictor.onnx", "wb") as f:
    f.write(onnx_model.SerializeToString())

print("✅ Model exported to ONNX successfully!")
