import json
import random


# Test data for the original json file
test_data = [
    ("08:00:00", random.randint(50, 60)),
    ("08:00:30", random.randint(150, 200)), # Outlier
    ("08:01:00", random.randint(50, 60)),
    ("08:01:30", random.randint(50, 60)),
    ("08:02:00", random.randint(50, 60)),
    ("08:02:30", random.randint(50, 60)),
    ("08:03:00", random.randint(50, 60)),
    ("08:03:30", random.randint(50, 60)),
    ("08:04:00", random.randint(50, 60)),
    ("08:04:30", random.randint(50, 60)),
    ("08:05:00", random.randint(50, 60)),
    ("08:05:30", random.randint(50, 60)),
    ("08:06:00", random.randint(50, 60)),
    ("08:06:30", random.randint(150, 200)), # Outlier
    ("08:07:00", random.randint(50, 60)),
    ("08:07:30", random.randint(50, 60)),
    ("08:08:00", random.randint(50, 60)),
    ("08:08:30", random.randint(50, 60)),
    ("08:09:00", random.randint(50, 60)),
    ("08:09:30", random.randint(50, 60)),
    ("08:10:00", random.randint(50, 60)),
    ("08:10:30", random.randint(50, 60)),
    ("08:11:00", random.randint(50, 60)),
    ("08:11:30", random.randint(50, 60)),
    ("08:12:00", random.randint(150, 200)), # Outlier
    ("08:12:30", random.randint(50, 60)),
    ("08:13:00", random.randint(50, 60)),
    ("08:13:30", random.randint(50, 60)),
    ("08:14:00", random.randint(50, 60)),
    ("08:14:30", random.randint(50, 60)),
    ("08:15:00", random.randint(50, 60)),
]
    

# Writing the test data to the json file
file_path = 'timeseries.json'
with open(file_path, 'w') as file:
    json.dump(test_data, file)