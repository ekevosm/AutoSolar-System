import statistics
import json
from datetime import datetime, time, timedelta

# Θεωρείται δεδομένο ότι τα timestamps είναι αποθηκευμένα στη μορφή %H:%M:%S (ώρα:λεπτά:δευτερόλεπτα)

# Συνάρτηση που δέχεται μια λίστα απο δυάδες (timestamp, data point) και επιστρέφει την καθαρισμένη λίστα

def clean_timeseries(timeseries):    
    cleaned_timeseries = []
   
    # Υπολογισμός μέσου όρου και τυπικής απόκλισης
    data_points = [data_point for _, data_point in timeseries]
    mean = statistics.mean(data_points)
    std_dev = statistics.stdev(data_points)
    
    # Για κάθε δυάδα timestamp και data point στο timeseries εντός του δωσμένου interval
    for timestamp, data_point in timeseries:
        
        # Έλεγχος αν το data point είναι εντός του εύρους μέσου όρου ± 2 * τυπική απόκλιση
        if abs(data_point - mean) <= 2 * std_dev:
            cleaned_timeseries.append([timestamp, data_point])
        else:
            print(f"Outlier detected: {data_point} , {timestamp}")
    
    return cleaned_timeseries


file_path = 'timeseries.json'
with open(file_path, 'r') as file:
    timeseries = json.load(file)


time_interval = 5  # Καθορισμός του interval σε λεπτά


sliced_timeseries = []  # Λίστα απο λίστες με τα δεδομένα ανά 5 λεπτά
current_interval = [] 
previous_time = None


for timestamp, data_point in timeseries: 
    time_obj = datetime.strptime(timestamp, "%H:%M:%S").time()  # Μετατροπή του timestamp σε time object εδώ 
    if previous_time is None:  # για το πρώτο διάστημα
        previous_time = time_obj

    if (time_obj.minute // time_interval) != (previous_time.minute // time_interval):  
        # θα προκύψουν και πιο μικρά διαστήματα στην αρχή και στο τέλος κάθε ώρας αλλά θεωρείται αμελητέο
        # π.χ. αν τα δεδομένα ξεκινάνε απο το 7ο λεπτό της ώρας, το πρώτο διάστημα θα είναι 3 λεπτά, διότι
        # θα αλλάξει interval στο 10ο λεπτό με τον συγκεκριμένο τρόπο
        sliced_timeseries.append(current_interval)
        current_interval = []
        current_interval.append([timestamp, data_point])
        previous_time = time_obj
    else:
        current_interval.append([timestamp, data_point])




# Καθαρισμός των δεδομένων ανά 5 λεπτά
cleaned_data = []
for interval in sliced_timeseries:
    cleaned_interval = clean_timeseries(interval)
    cleaned_data.extend(cleaned_interval)  # προσθήκη των καθαρισμένων δεδομένων στο τέλος της cleaned_data


# Γράψιμο του cleaned_timeseries στο ίδιο αρχείο
with open(file_path, 'w') as file:
    json.dump(cleaned_data, file)
