<div align="center">
<h1>Comparative Study for Backend in AI-Driven APIs</h1> 
    
<i>Benchmark Faster, Innovate Smarter, Lead the Future</i><br></br>

![last commit](https://img.shields.io/github/last-commit/tanishq0917t/Comparative-Study-for-Backend-in-AI-Driven-APIs?style=flat&color=blue)
![languages](https://img.shields.io/badge/languages-4-blue)
    
![Express](https://img.shields.io/badge/Express-black?logo=express&logoColor=white)
![JSON](https://img.shields.io/badge/JSON-000000?logo=json&logoColor=white)
![Markdown](https://img.shields.io/badge/Markdown-000000?logo=markdown&logoColor=white)
![npm](https://img.shields.io/badge/npm-CB3837?logo=npm&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?logo=javascript&logoColor=black)
![Gradle](https://img.shields.io/badge/Gradle-02303A?logo=gradle&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B&logoColor=white)
![XML](https://img.shields.io/badge/XML-0065AE?logo=xml&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?logo=python&logoColor=white)
![ONNX](https://img.shields.io/badge/ONNX-005CED?logo=onnx&logoColor=white)
![Docker](https://img.shields.io/badge/Docker-2496ED?logo=docker&logoColor=white)

</div>

### Introduction
Conducted a comparative study of modern back-end frameworks and languages, including Python, C++, Java, and Node.js, for serving AI-driven APIs. Using a real-world use case of predicting second-hand iPhone prices, I implement and benchmark inference APIs built with each backend. I evaluate them on multiple metrics, including latency, throughput, memory usage, and developer experience.

### Programming Languages & Frameworks
<ul>
<li> <b>Python</b> - FastAPI </li>
<li> <b>NodeJS</b> - Express </li>
<li> <b>C++</b> - Crow </li>
<li> <b>Java</b> - Spring Boot </li>
</ul>

<hr>

### How to set up FastAPI Environment
Execute the following commands to install dependencies
1. ``` pip install fastapi uvicorn python-dotenv jinja2 requests ```
2. ``` pip install pandas scikit-learn onnx onnxruntime ```

Execute the below command to start the FastAPI Server
1. ``` cd fastapi_src ``` 
2. ``` uvicorn main:app --reload ```
<br></br>
![FastAPI Server](assets/fastapi_server.png)
<hr>

### How to set up C++ Environment

1. ``` cd cpp_src ``` \
Now you will see 2 zip files [They are linux/mac based libraries, for windows you can find them on github] - asio.zip and onnxruntime-linux-x64-1.20.0.zip, You need to unzip them
2. ``` unzip asio.zip ; unzip onnxruntime-linux-x64-1.20.0.zip ```
You can also directly execute and start the server by
3. ``` ./predict_iphone ``` \
Or you can compile the <b>main.cpp</b> on your system. For that, you need to set 2 PATH variables
```
export ONNX_RUNTIME_DIR="onnxruntime-linux-x64-1.20.0" #You can also give an absolute path
export ONNX_LIB_PATH="onnxruntime-linux-x64-1.20.0/lib" #You can also give an absolute path

g++ main.cpp -o predict_iphone -std=c++17 \
    -I${ONNX_RUNTIME_DIR}/include \
    -I. \
    -Iasio/asio/include \
    -L${ONNX_LIB_PATH} \
    -lonnxruntime \
    -Wl,-rpath,${ONNX_LIB_PATH} \
    -pthread
```
To send a request using cURL you can use the following command
```
curl -X POST http://localhost:8080/predict \
    -H "Content-Type: application/json" \
    -d '{
        "battery_health": 90,
        "purchase_year": 2022,
        "battery_cycles": 300,
        "damage_percent": 15,
        "iphone_version": "iPhone 15"
    }'
```
<br></br>
![C++ Server](assets/cpp_server.png)
<hr>

### How to set up NodeJS Environment
1. Install all the required packages
   ```
    npm install express body-parser onnxruntime-node
   ```
2. To run the server, execute the following command
   ```
    node server.js
   ```
3. To test the /predict endpoint, execute the following command.
   ```
   curl -X POST http://localhost:3000/predict \
   -H "Content-Type: application/json" \
   -d '{
        "battery_health": 85,
        "purchase_year": 2022,
        "battery_cycles": 350,
        "damage_percent": 5.5,
        "iphone_version_code": 12
   }'
   ```
<br></br>
![Express Server](assets/express_server.png)
<hr>

### How to set up Java Environment
1. Make sure you have Java 17 and Maven installed
   ```
    brew install openjdk@17 #For Mac
    sudo apt install openjdk@17 #For Linux

    brew install maven #For mac
    sudo apt install maven #For Linux
   ```
2. Execute the below command to generate the JAR file, located in target/
    ```
    mvn clean install
    ```
3. Execute the below command to execute the Spring Boot application
    ```
    java -jar target/{app_name}-0.0.1-SNAPSHOT.jar #replace app_name with your directory name
    ```
4. In a separate terminal, execute the below cURL command to test the endpoint
    ```
    curl -X POST http://localhost:8080/predict \
   -H "Content-Type: application/json" \
   -d '{
        "battery_health": 85,
        "purchase_year": 2022,
        "battery_cycles": 350,
        "damage_percent": 5.5,
        "iphone_version_code": 12
   }'
    ```
<br></br>
![Spring Boot Server](assets/spring_server.png)
<hr>
