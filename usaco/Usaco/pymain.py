import pandas as pd#python3 pymain.py
from sklearn.preprocessing import OneHotEncoder

# Example DataFrame
df = pd.DataFrame({
    "Color": ["Red", "Blue", "Green", "Red", "Blue"]
})

print("Original DataFrame:")
print(df)

# Create the encoder
encoder = OneHotEncoder(sparse_output=False)

# Fit and transform
encoded = encoder.fit_transform(df)

# Convert back to a DataFrame
encoded_df = pd.DataFrame(
    encoded,
    columns=encoder.get_feature_names_out()
)

print("\nOne-Hot Encoded DataFrame:")
print(encoded_df)