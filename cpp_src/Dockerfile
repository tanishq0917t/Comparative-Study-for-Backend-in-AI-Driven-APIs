FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

ENV ONNX_RUNTIME_DIR=onnxruntime-linux-x64-1.20.0
ENV ONNX_LIB_PATH=$ONNX_RUNTIME_DIR/lib

WORKDIR /app

COPY . .

# Compile the application
RUN g++ main.cpp -o predict_iphone -std=c++17 \
    -I$ONNX_RUNTIME_DIR/include \
    -I. \
    -Iasio/asio/include \
    -L$ONNX_LIB_PATH \
    -lonnxruntime \
    -Wl,-rpath,$ONNX_LIB_PATH \
    -pthread

# Expose Crow app port
EXPOSE 18080

# Run the compiled binary
CMD ["./predict_iphone"]