#include <Arduino.h>
#include <DHT.h>

// Pin dan tipe sensor DHT11
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Serial Monitor
  Serial.begin(115200);

  // UART2 untuk komunikasi dengan ESP32-2
  // RX2 = GPIO 16, TX2 = GPIO 17
  Serial2.begin(115200);
  Serial2.setTimeout(5000);

  // Inisialisasi sensor DHT11
  dht.begin();

  Serial.println("ESP32-1 siap mengirim data.");
}

void loop() {
  // Membaca suhu dan kelembapan
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Memeriksa apakah pembacaan sensor berhasil
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Gagal membaca sensor DHT11.");
    delay(5000);
    return;
  }

  // Membuat data dalam format:
  // suhu,kelembapan
  String data = String(temperature, 1) + "," + String(humidity, 1);

  // Menampilkan data pada Serial Monitor
  Serial.println("Data sensor:");
  Serial.print("Suhu       : ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Kelembapan : ");
  Serial.print(humidity);
  Serial.println(" %");

  // Mengirim data ke ESP32-2 melalui UART
  Serial2.println(data);

  Serial.println("Data dikirim ke ESP32-2.");
  Serial.println("-------------------------");

  // Menunggu 5 detik sebelum pembacaan berikutnya
  delay(5000);
}
