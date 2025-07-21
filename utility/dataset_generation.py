import pandas as pd
import numpy as np
import random

# Define possible iPhone versions
iphone_versions = [
    "iPhone 11", "iPhone 11 Pro", "iPhone 12", "iPhone 12 Pro",
    "iPhone 13", "iPhone 13 Pro", "iPhone 14", "iPhone 14 Pro",
    "iPhone 15", "iPhone 15 Pro", "iPhone SE (2nd Gen)", "iPhone SE (3rd Gen)"
]

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
    "iPhone 11": 30000,
    "iPhone 11 Pro": 40000,
    "iPhone 12": 45000,
    "iPhone 12 Pro": 55000,
    "iPhone 13": 50000,
    "iPhone 13 Pro": 60000,
    "iPhone 14": 55000,
    "iPhone 14 Pro": 65000,
    "iPhone 15": 60000,
    "iPhone 15 Pro": 70000,
    "iPhone SE (2nd Gen)": 25000,
    "iPhone SE (3rd Gen)": 30000,
}

# Calculate price with degradation
prices = []
for i in range(n):
    base_price = version_base_price[data["iphone_version"][i]]
    age = 2025 - data["purchase_year"][i]
    depreciation = (100 - data["battery_health"][i]) * 0.01
    damage_penalty = data["damage_percent"][i] * 50  # ₹50 per 1% damage
    cycle_penalty = max(0, data["battery_cycles"][i] - 500) * 10  # ₹10 per extra cycle
    final_price = base_price * (1 - 0.15 * age) * (1 - depreciation) - damage_penalty - cycle_penalty
    prices.append(max(2000, round(final_price)))  # Minimum price ₹2000

data["price"] = prices
df = pd.DataFrame(data)
# Save the dataset to a CSV file
df.to_csv("dataset/iphone_prices_dataset.csv", index=False)