<div align="center">
<h1>Comparative Study for Backend in AI-Driven APIs</h1> 
    
<i>Benchmark Faster, Innovate Smarter, Lead the Future</i><br></br>
    
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

### Docker Images 
<table>
    <thead>
        <tr>
            <th>S. No</th>
            <th>Image Name</th>
            <th>Framework</th>
            <th>Port Exposed</th>
            <th>Link</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>1</td>
            <td>fastapi-onnx</td>
            <td>FastAPI - Python</td>
            <td>5050</td>
            <td><a href="https://hub.docker.com/r/tanishq1710h/fastapi-onnx">Click</a></td>
        </tr>
        <tr>
            <td>2</td>
            <td>crow-onnx</td>
            <td>Crow - C++</td>
            <td>18080</td>
            <td><a href="https://hub.docker.com/r/tanishq1710h/crow-onnx">Click</a></td>
        </tr>
        <tr>
            <td>3</td>
            <td>express-onnx</td>
            <td>Express - NodeJS</td>
            <td>3000</td>
            <td><a href="https://hub.docker.com/r/tanishq1710h/express-onnx">Click</a></td>
        </tr>
        <tr>
            <td>4</td>
            <td>springboot-onnx</td>
            <td>Springboot - Java</td>
            <td>8080</td>
            <td><a href="https://hub.docker.com/r/tanishq1710h/springboot-onnx">Click</a></td>
        </tr>
    </tbody>
</table>
<hr>

<h2>How to run application using Docker Containers</h2> 

1. Check if Docker is installed, if not visit - <a href="https://docs.docker.com/engine/install/">Docker Installation</a>
   ```
   docker -v
   ```
2. To pull images from Docker Hub to your local machine, execute the following command
   ```
   docker pull tanishq1710h/fastapi-onnx
   docker pull tanishq1710h/crow-onnx
   docker pull tanishq1710h/express-onnx
   docker pull tanishq1710h/springboot-onnx
   ```
3. To run a Docker image, execute the following command (Replace image name)
   ```
   docker run --name {image_name} -p {port_number}:{port_number} {container_name}
   ```
   example,
   ```
   docker run --name fastapi-onnx -p 5050:5050 fastapi-onnx-container
   ```
   To run in the background, use the  -d flag
   ```
   docker run -d --name fastapi-onnx -p 5050:5050 fastapi-onnx-container
   ```
4. Now you can send the request, check using the cURL command -- Replace {app_port_number} with the specific container port number.
   ```
   curl -X POST http://localhost:{app_port_number}/predict \
    -H "Content-Type: application/json" \
    -d '{
        "battery_health": 90,
        "purchase_year": 2024,
        "battery_cycles": 300,
        "damage_percent": 15,
        "iphone_version_code": 13
    }'
   ```

<hr>

<h2>If you don't want to use Docker, you can manually set up all frameworks</h2>

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
<br></br>
![Express Server](assets/express_server.png)
<hr>

### How to set up a Java Environment
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
<br></br>
![Spring Boot Server](assets/spring_server.png)
<hr>
