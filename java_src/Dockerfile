FROM ubuntu:22.04

# Install dependencies and Java
RUN apt-get update && apt-get install -y \
    openjdk-17-jdk \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Set environment variables
ENV APP_HOME=/app
WORKDIR $APP_HOME

# Copy JAR
COPY target/*.jar app.jar

# Expose port
EXPOSE 8080

# Run app
ENTRYPOINT ["java", "-jar", "app.jar"]