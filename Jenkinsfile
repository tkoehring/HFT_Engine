pipeline {
    agent { label 'cpp' }

    options {
        timestamps()
        disableConcurrentBuilds()
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Tool Versions') {
            steps {
                sh 'cmake --version'
                sh 'ninja --version'
                sh 'g++ --version'
                sh 'clang++-18 --version || clang++ --version'
                sh 'llvm-symbolizer-18 --version || llvm-symbolizer --version'
            }
        }

        stage('GCC Debug') {
            steps {
                sh 'cmake --preset linux-debug'
                sh 'cmake --build --preset linux-debug'
                sh 'ctest --preset linux-debug --output-on-failure -j1'
            }
        }

        stage('GCC ASan UBSan') {
            steps {
                sh 'cmake --preset linux-asan-ubsan'
                sh 'cmake --build --preset linux-asan-ubsan'
                sh 'ctest --preset linux-asan-ubsan --output-on-failure -j1'
            }
        }

        stage('Clang Debug') {
            steps {
                sh 'cmake --preset linux-clang-debug'
                sh 'cmake --build --preset linux-clang-debug'
                sh 'ctest --preset linux-clang-debug --output-on-failure -j1'
            }
        }

        stage('Clang ASan UBSan') {
            steps {
                sh 'cmake --preset linux-clang-asan-ubsan'
                sh 'cmake --build --preset linux-clang-asan-ubsan'
                sh 'ctest --preset linux-clang-asan-ubsan --output-on-failure -j1'
            }
        }
    }

    post {
        always {
            cleanWs()
        }
    }
}