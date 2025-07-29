<div align="center">
  <h1>📊 Comparative Study for Backend in AI-Driven APIs</h1>
  <i>Benchmark Faster, Innovate Smarter, Lead the Future</i><br><br>

  ![Python](https://img.shields.io/badge/Python-3776AB?logo=python&logoColor=white)
  ![Node.js](https://img.shields.io/badge/Node.js-339933?logo=nodedotjs&logoColor=white)
  ![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B&logoColor=white)
  ![Java](https://img.shields.io/badge/Java-007396?logo=java&logoColor=white)
  ![ONNX](https://img.shields.io/badge/ONNX-005CED?logo=onnx&logoColor=white)
  ![Docker](https://img.shields.io/badge/Docker-2496ED?logo=docker&logoColor=white)
</div>

---

## 🔍 Overview

This project conducts a comparative study of backend frameworks and languages—**Python (FastAPI), Node.js (Express), C++ (Crow), and Java (Spring Boot)**—for serving real-time AI inference APIs. Using a practical use case (predicting second-hand iPhone prices), it benchmarks:

- 🔁 **Latency**
- 🚀 **Throughput**
- 🔥 **CPU Usage**
- 🧠 **Memory Footprint**
- 👨‍💻 **Developer Experience**

---

## 📚 Contents

- [Overview](#-overview)
- [Technologies Used](#-technologies-used)
- [Docker Setup](#-docker-images)
- [Manual Setup](#-manual-setup-no-docker)
- [API Usage](#-example-api-usage)
- [Benchmark Metrics](#-benchmark-metrics-coming-soon)
- [License](#-license)
- [Citation](#-citation)

---

## 🛠️ Technologies Used

- **Python** → FastAPI [`/fastapi_src`](fastapi_src)
- **C++** → Crow [`/cpp_src`](cpp_src)
- **Node.js** → Express [`/nodejs_src`](nodejs_src)
- **Java** → Spring Boot [`/java_src`](java_src)

---

## 🐳 Docker Images

| S. No | Image Name         | Framework         | Port | Docker Hub |
|-------|---------------------|-------------------|------|-------------|
| 1     | fastapi-onnx        | FastAPI (Python)  | 5050 | [Link 🔗](https://hub.docker.com/r/tanishq1710h/fastapi-onnx) |
| 2     | crow-onnx           | Crow (C++)        | 18080| [Link 🔗](https://hub.docker.com/r/tanishq1710h/crow-onnx) |
| 3     | express-onnx        | Express (NodeJS)  | 3000 | [Link 🔗](https://hub.docker.com/r/tanishq1710h/express-onnx) |
| 4     | springboot-onnx     | Spring Boot (Java)| 8080 | [Link 🔗](https://hub.docker.com/r/tanishq1710h/springboot-onnx) |

---

## 📦 How to Run (Using Docker)

1. **Install Docker:** [Get Docker](https://docs.docker.com/engine/install/)
   ```bash
   docker -v
   ```

2. **Pull images from Docker Hub:**
   ```bash
   docker pull tanishq1710h/fastapi-onnx
   docker pull tanishq1710h/crow-onnx
   docker pull tanishq1710h/express-onnx
   docker pull tanishq1710h/springboot-onnx
   ```

3. **Run any image:**
   ```bash
   docker run --rm -d --name fastapi-onnx -p 5050:5050 tanishq1710h/fastapi-onnx
   ```

4. **Test API with curl:**
   ```bash
   curl -X POST http://localhost:5050/predict      -H "Content-Type: application/json"      -d '{
       "battery_health": 90,
       "purchase_year": 2024,
       "battery_cycles": 300,
       "damage_percent": 15,
       "iphone_version_code": 13
     }'
   ```

---

## 🧰 Manual Setup (No Docker)

<details>
<summary><strong>🔧 Setup FastAPI (Python)</strong></summary>

```bash
pip install fastapi uvicorn python-dotenv jinja2 requests
pip install pandas scikit-learn onnx onnxruntime
cd fastapi_src
uvicorn main:app --reload
```

<p align="center">
  <img src="assets/fastapi_server.png" width="70%" />
</p>
</details>

---

<details>
<summary><strong>🔧 Setup C++ (Crow)</strong></summary>

```bash
cd cpp_src
unzip asio.zip
unzip onnxruntime-linux-x64-1.20.0.zip
```

**Quick Run:**
```bash
./predict_iphone
```

**Or Compile Manually:**

```bash
export ONNX_RUNTIME_DIR="onnxruntime-linux-x64-1.20.0"
export ONNX_LIB_PATH="$ONNX_RUNTIME_DIR/lib"

g++ main.cpp -o predict_iphone -std=c++17     -I${ONNX_RUNTIME_DIR}/include -I. -Iasio/asio/include     -L${ONNX_LIB_PATH} -lonnxruntime -Wl,-rpath,${ONNX_LIB_PATH} -pthread
```

<p align="center">
  <img src="assets/cpp_server.png" width="70%" />
</p>
</details>

---

<details>
<summary><strong>🔧 Setup Node.js (Express)</strong></summary>

```bash
npm install express body-parser onnxruntime-node
node server.js
```

<p align="center">
  <img src="assets/express_server.png" width="70%" />
</p>
</details>

---

<details>
<summary><strong>🔧 Setup Java (Spring Boot)</strong></summary>

Install Java 17 and Maven:

```bash
# macOS
brew install openjdk@17 maven

# Linux
sudo apt install openjdk-17-jdk maven
```

Build and Run:

```bash
cd java_src
mvn clean install
java -jar target/{app_name}-0.0.1-SNAPSHOT.jar
```

<p align="center">
  <img src="assets/spring_server.png" width="70%" />
</p>
</details>

---

## 🧪 Example API Usage

Here’s the JSON format accepted by all four backends:

```json
{
  "battery_health": 90,
  "purchase_year": 2024,
  "battery_cycles": 300,
  "damage_percent": 15,
  "iphone_version_code": 13
}
```

---

## 📊 Benchmark Metrics (Coming Soon)

Metrics collected using tools like ApacheBench (`ab`), `docker stats`, and custom logging:

- ⏱️ **Latency**: avg, P95, max
- 🔁 **Throughput**: requests/sec
- 🧠 **Memory**: peak usage in MiB
- 🔥 **CPU**: percent of logical core usage
- 📈 **Comparative graphs** to visualize trends across languages

> 📌 Stay tuned — full benchmark visualizations coming in the final paper.

---

## 📄 License

This project is released under the [MIT License](LICENSE).

---

## ✍️ Citation

If this project helps your research, please consider citing it or crediting the repository:

```plaintext
Tanishq Rawat, "Comparative Study for Backend in AI-Driven APIs", 2025. GitHub Repo.
https://github.com/tanishq0917t/Comparative-Study-for-Backend-in-AI-Driven-APIs
```

---
