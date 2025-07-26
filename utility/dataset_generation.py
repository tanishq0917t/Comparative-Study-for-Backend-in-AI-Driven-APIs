import pandas as pd
import numpy as np
import random

# Define iPhone versions and map to numbers
iphone_versions = [
    "iPhone 11", "iPhone 11 Pro", "iPhone 12", "iPhone 12 Pro",
    "iPhone 13", "iPhone 13 Pro", "iPhone 14", "iPhone 14 Pro",
    "iPhone 15", "iPhone 15 Pro", "iPhone SE (2nd Gen)", "iPhone SE (3rd Gen)",
    "iPhone 16", "iPhone 16 Pro"
]
iphone_version_mapping = {version: idx for idx, version in enumerate(iphone_versions)}

# Generate synthetic dataset
n = 1000
data = {
    "battery_health": np.random.randint(60, 101, n),
    "purchase_year": np.random.randint(2018, 2024, n),
    "battery_cycles": np.random.randint(100, 1000, n),
    "damage_percent": np.random.uniform(0, 50, n).round(2),
    "iphone_version": np.random.choice(iphone_versions, n),
}

# Assign base prices and apply depreciation
version_base_price = {
  "iPhone 11": 64900,
  "iPhone 11 Pro": 99900,
  "iPhone 12": 79900,
  "iPhone 12 Pro": 119900,
  "iPhone 13": 79900,
  "iPhone 13 Pro": 119900,
  "iPhone 14": 79900,
  "iPhone 14 Pro": 129900,
  "iPhone 15": 79900,
  "iPhone 15 Pro": 134900,
  "iPhone SE (2nd Gen)": 42500,
  "iPhone SE (3rd Gen)": 43900,
  "iPhone 16": 79900,
  "iPhone 16 Pro": 119900
}

# Calculate price with degradation
prices = []
iphone_version_codes = []
for i in range(n):
    version = data["iphone_version"][i]
    base_price = version_base_price[version]
    age = 2025 - data["purchase_year"][i]
    depreciation = (100 - data["battery_health"][i]) * 0.01
    damage_penalty = data["damage_percent"][i] * 50  # ₹50 per 1% damage
    cycle_penalty = max(0, data["battery_cycles"][i] - 500) * 10  # ₹10 per extra cycle
    final_price = base_price * (1 - 0.15 * age) * (1 - depreciation) - damage_penalty - cycle_penalty
    prices.append(max(2000, round(final_price)))  # Minimum price ₹2000
    iphone_version_codes.append(iphone_version_mapping[version])

# Prepare final dataframe
data["iphone_version_code"] = iphone_version_codes
data["price"] = prices
df = pd.DataFrame(data)

# Drop the string column
df = df.drop(columns=["iphone_version"])

# Save to CSV
df.to_csv("dataset/iphone_prices_dataset.csv", index=False)

# Optional: Save mapping for inference use
pd.Series(iphone_version_mapping).to_csv("dataset/iphone_version_mapping.csv")