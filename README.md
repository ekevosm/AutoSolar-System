# AutoSolar-System
Solar Energy Project

## Σκοπός του έργου

Στόχος της κατασκευής είναι η εφαρμογή τεχνολογιών του Διαδικτύου των Πραγμάτων (ΙοΤ) για την παρακολούθηση της παραγωγής ηλεκτρικής ενέργειας από τον ήλιο και της κατανάλωσής της. Μέσα από την καταγραφή και οπτικοποίηση των δεδομένων παραγωγής και κατανάλωσης ηλεκτρικής ενέργειας  αναμένεται η καλλιέργεια συνήθειών και πρακτικών φιλικότερων προς το περιβάλλον με στόχο την αποδοτική διαχείριση και εξοικονόμηση ηλεκτρικής ενέργειας. 

Το έργο μας εντάσσεται στην κατηγορία της «Πράσινης Παραγωγής Ενέργειας» και της «Εξοικονόμησης Ενέργειας.

Ποιο συγκεκριμένα, θα κατασκευάσουμε διάταξη στην οποία θα παράγεται ηλεκτρική ενέργεια από φωτοβολταϊκό πάνελ και θα αποθηκεύεται σε μπαταρία. Στη διάταξη θα υπάρχει υποδοχή USB για τη φόρτιση κινητού τηλεφώνου από την ενέργεια που παράγεται από τον ήλιο. Θα συνδεθεί επίσης λάμπα  η οποία θα αντλεί ενέργεια από τη φορτισμένη μπαταρία. Η λειτουργία της διάταξης θα παρακολουθείται από αισθητήρες ρεύματος ώστε να καταγράφονται και να οπτικοποιούνται  τα δεδομένα παραγωγής και κατανάλωσης ηλεκτρικής ενέργειας, προσομοιώνοντας με τον τρόπο αυτό τη λειτουργία ενός έξυπνου μετρητή. 
Γενικότερα, η εξοικείωση με τη λειτουργία των έξυπνων συσκευών για τον έλεγχο και τη μείωση της κατανάλωσης ηλεκτρικής ενέργειας, αναμένεται να συμβάλει στην αλλαγή ενεργειακών συμπεριφορών των εμπλεκομένων μαθητών. 

## ΤΕΧΝΙΚΑ ΧΑΡΑΚΤΗΡΙΣΤΙΚΆ – ΠΕΡΙΓΡΑΦΗ ΤΟΥ ΕΡΓΟΥ

Βασικό στοιχείο της διάταξης αποτελεί το φωτοβολταϊκό πάνελ το οποίο φορτίζει την μπαταρία μόλυβδου με την υποστήριξη ενός ελεγκτή ηλιακής φόρτισης.  Ο ελεγκτής διαθέτει υποδοχή USB από την οποία μπορεί να γίνει φόρτιση κινητού τηλεφώνου.

Η καταγραφή της ηλεκτρικής ενέργειας που παράγεται από το φωτοβολταϊκό πάνελ, αλλά και η κατανάλωση της ηλεκτρικής ενέργειας από τη λάμπα (ταινία led) πραγματοποιείται με χρήση αισθητήρων  Voltage Sensor Module και Current Sensor Module. Τα κυκλώματα των αισθητήρων συνδέονται με τον μικροελεγκτή Arduino Uno. Οι τιμές εμφανίζονται σε πραγματικό χρόνο σε Display Character LCD.

Ως εξυπηρετητής για την αποθήκευση, επεξεργασία και οπτικοποίηση των δεδομένων θα χρησιμοποιηθεί ένα Raspberry Pi. Η σύνδεση και μεταφορά δεδομένων μεταξύ του Arduino και του Raspberry Pi θα γίνεται σειριακά, μέσω της θύρας USB, ενώ η πρόσβαση στον εξυπηρετητή θα γίνεται μέσω του δικτύου Wifi του σχολείου. Σχεδιάζεται επίσης να γίνει σύνδεση με το Arduino Cloud για την αποθήκευση και οπτικοποίηση των δεδομένων.

Οι γλώσσες προγραμματισμού που έχουν επιλεγεί είναι το Arduino IDE και η Python.

Για την διαχείριση των ΙοΤ συσκευών, την αποθήκευση και οπτικοποίηση των δεδομένων θα αξιοποιηθούν οι παρακάτω τεχνολογίες ελεύθερου/ανοιχτού λογισμικού:
-	**NodeRed** για την επικοινωνία του συστήματος μέτρησης με τον εξυπηρετητή για την αρχική απεικόνιση και την αποθήκευση των δεδομένων, καθώς και την αποστολή μηνυμάτων ηλεκτρονικού ταχυδρομείου σε περίπτωση έκτακτης ανάγκης.
-	**InfluxDB** ως σύστημα διαχείρισης βάσης δεδομένων
-	**Grafana** για την οπτικοποίηση των δεδομένων

Τα υλικά που θα απαιτηθούν καθώς και το αντίστοιχο κόστος καταγράφονται αναλυτικά στον παρακάτω πίνακα.

|Απαιτούμενος εξοπλισμός |	Ποσότητα |	Ενδεικτικό Κόστος (€) |
| ----------- | ----------- | ----------- | 
| RASPBERRY PI 4 Model B* |	<div align="center">1 </div> |	<div align="right"> 80,0</div> |
| ARDUINO UNO R3* |	<div align="center">1  </div> |	<div align="right"> 24,0</div> |
|	VOLTAGE SENSOR MODULE FOR ROBOT ARDUINO DC	|	<div align="center">1 </div> |	<div align="right"> 1,5 </div> |
|	RANGE CURRENT SENSOR MODULE	|	<div align="center">2 </div> |	<div align="right"> 9,0 </div> |
|	ΦΩΤΟΒΟΛΤΑΪΚΗ ΚΥΨΕΛΗ	|	<div align="center">1 </div> |	<div align="right"> 20,0 </div> |
|	SOLAR BATTERY CHARGER REGULATOR	|	<div align="center">1 </div> |	<div align="right"> 13,0 </div> |
|	ΜΠΑΤΑΡΙΑ ΜΟΛΥΒΔΟΥ 12V	|	<div align="center">1 </div> |	<div align="right"> 12,5 </div> |
|	LED STRIP	|	<div align="center">1 </div> |	<div align="right"> 4,0 </div> |
|	RELAY MODULE	|	<div align="center">1 </div> |	<div align="right"> 2,0</div> |
|	DISPLAY CHARACTER LCD	|	<div align="center">1 </div> |	<div align="right"> 6,0</div> |
| <div align="right">**ΣΥΝΟΛΟ** </div> ||	 	 	<div align="right"> **172,0**</div> |

*Στο σχολείο μας διαθέτουμε αυτά τα δύο μέρη του εξοπλισμού, οπότε το κόστος για το συγκεκριμένο έργο είναι περίπου 68€
