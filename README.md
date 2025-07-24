# Comparitive Study for Backend in AI Driven APIs

### Introduction
Conduct a comparative study of modern back-end frameworks and languages, including Python, C++, Rust, and Node.js, for serving AI-driven APIs. Using a real-world use case of predicting second-hand iPhone prices, I implement and benchmark inference APIs built with each backend. I evaluate them on multiple metrics, including latency, throughput, memory usage, and developer experience.

### Programming Languages & Frameworks
<ul>
<li> <b>Python</b> - FastAPI </li>
<li> <b>NodeJS</b> - Express </li>
<li> <b>C++</b> - Crow </li>
<li> Rust </li>
</ul>

### How to setup FastAPI Environment
Execute below commands to install dependencies
1. ``` pip install fastapi uvicorn python-dotenv jinja2 requests ```
2. ``` pip install pandas scikit-learn onnx onnxruntime ```

Execute the below command to start FastAPI Server
1. ``` cd fastapi_src ``` 
2. ``` uvicorn main:app --reload ```
