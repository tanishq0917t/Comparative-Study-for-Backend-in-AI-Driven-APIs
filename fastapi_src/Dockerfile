FROM ubuntu:22.04

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install Python, pip, and system dependencies
RUN apt-get update && \
    apt-get install -y python3.11 python3.11-venv python3.11-dev python3-pip build-essential && \
    ln -sf python3.11 /usr/bin/python3 && \
    pip3 install --upgrade pip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy requirements file first to leverage Docker cache
COPY requirements.txt .

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Copy application code
COPY . .

# Expose port FastAPI runs on
EXPOSE 5050

# Run FastAPI app
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "5050"]