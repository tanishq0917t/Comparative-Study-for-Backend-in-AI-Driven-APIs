# Comparitive Study for Backend in AI Driven APIs

### Introduction
Conduct a comparative study of modern back-end frameworks and languages, including Python, Go, Rust, and Node.js, for serving AI-driven APIs. Using a real-world use case of predicting second-hand iPhone prices, I implement and benchmark inference APIs built with each backend. I evaluate them on multiple metrics, including latency, throughput, memory usage, and developer experience.

### Programming Languages & Frameworks
<ul>
<li> Python - FastAPI </li>
<li> NodeJS - Express </li>
<li> GoLang </li>
<li> Rust </li>
</ul>

### How to setup FastAPI Environment
Execute below commands to install dependencies
1. ``` pip install fastapi uvicorn python-dotenv jinja2 requests ```
2. ``` pip install pandas scikit-learn onnx onnxruntime ```

Execute the below command to start FastAPI Server
``` cd fastapi_src; uvicorn main:app --reload  ```