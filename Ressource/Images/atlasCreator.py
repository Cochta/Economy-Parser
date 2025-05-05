import os
import math
from PIL import Image
from pathlib import Path
import csv

# Configuration
input_folder = Path("1.21.5")  # folder containing PNGs
output_image = "1.21.5_atlas.png"
output_metadata = "1.21.5_atlas_metadata.csv"  # Simple metadata output
padding = 2  # pixels between images

# Collect PNGs
png_files = sorted([f for f in input_folder.glob("*.png")])
if not png_files:
    print("No PNG files found in folder:", input_folder)
    exit(1)

# Load images
images = [Image.open(f) for f in png_files]
image_width, image_height = images[0].size

# Check for consistency
if any(im.size != (image_width, image_height) for im in images):
    print("All images must be the same size in this version.")
    exit(1)

# Compute atlas size (grid-based)
count = len(images)
grid_cols = math.ceil(math.sqrt(count))
grid_rows = math.ceil(count / grid_cols)
atlas_width = grid_cols * (image_width + padding) - padding
atlas_height = grid_rows * (image_height + padding) - padding

# Create atlas
atlas = Image.new("RGBA", (atlas_width, atlas_height))
metadata = []

for idx, img in enumerate(images):
    row = idx // grid_cols
    col = idx % grid_cols
    x = col * (image_width + padding)
    y = row * (image_height + padding)
    atlas.paste(img, (x, y))
    metadata.append(f"{png_files[idx].name},{x},{y},{image_width},{image_height}")

# Save output
atlas.save(output_image)
with open(output_metadata, "w") as meta_file:
    meta_file.write("\n".join(metadata))

print(f"Saved atlas to {output_image}")
print(f"Saved metadata to {output_metadata}")