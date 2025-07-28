FROM ubuntu:22.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install Node.js 18 and required tools
RUN apt-get update && \
    apt-get install -y curl gnupg build-essential && \
    curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && \
    apt-get install -y nodejs && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy package.json and lock file
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the rest of the code
COPY . .

# Expose port
EXPOSE 3000

# Run the app
CMD ["node", "server.js"]