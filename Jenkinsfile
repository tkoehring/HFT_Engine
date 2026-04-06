def runPreset(String preset) {
    sh """
        set -euxo pipefail
        cmake --preset ${preset}
        cmake --build --preset ${preset}
        ctest --preset ${preset} --output-on-failure -j1 --output-junit out/build/${preset}/ctest-results.xml
    """
}

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
                script {
                    runPreset('linux-debug')
                }
            }
        }

        stage('GCC ASan UBSan') {
            steps {
                script {
                    runPreset('linux-asan-ubsan')
                }
            }
        }

        stage('Clang Debug') {
            steps {
                script {
                    runPreset('linux-clang-debug')
                }
            }
        }

        stage('Clang ASan UBSan') {
            steps {
                script {
                    runPreset('linux-clang-asan-ubsan')
                }
            }
        }
    }

    post {
        always {
            junit allowEmptyResults: true, testResults: '**/ctest-results.xml'
            cleanWs()
        }
    }
}