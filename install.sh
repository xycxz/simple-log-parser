#!/usr/bin/env bash

set -euo pipefail

# Constants
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly SCRIPT_DIR
readonly BUILD_DIR="${SCRIPT_DIR}/build"

# Output helpers
info()    { echo "[INFO]  $*"; }
success() { echo "[OK]    $*"; }
error()   { echo "[ERROR] $*" >&2; }

# Verifies required tools are present
tool_check() {

    info "Checking required tools..."

    command -v cmake >/dev/null || {
        error "CMake is not installed."
        exit 1
    }

    if command -v g++ >/dev/null; then
        success "g++ detected."
    elif command -v clang++ >/dev/null; then
        success "clang++ detected."
    else
        error "No C++ compiler found (g++ or clang++ required)."
        exit 1
    fi
}

# Asks the user y/n
confirm_prompt() {
    local prompt_message="$1"
    local answer

    while true; do
        printf "%s [y/n]: " "${prompt_message}"
        read -r answer
        answer="${answer,,}"

        case "${answer}" in
            y) return 0 ;;
            n) return 1 ;;
            *) error "Invalid input '${answer}'. Please enter 'y' or 'n'." ;;
        esac
    done
}

# Removes the build directory if it exists, with user confirmation
cleanup() {
    if [[ -d "${BUILD_DIR}" ]]; then
        info "Existing build directory found at: ${BUILD_DIR}"

        if confirm_prompt "Delete it and rebuild from scratch?"; then
            rm -rf "${BUILD_DIR}"
            success "Build directory removed."
        else
            info "Keeping existing build directory. Proceeding with incremental build."
        fi
    fi
}

# Configure and builds the project
build() {

    info "Configuring project with CMake..."

    cmake -S "${SCRIPT_DIR}" -B "${BUILD_DIR}"
    success "CMake configuration complete."

    info "Building log_analyzer..."
    
    cmake --build "${BUILD_DIR}"
    success "Build complete."
    success "Binary available at: ${BUILD_DIR}/log_analyzer"
}

# Running the installer
main() {
    tool_check
    cleanup
    build
}

main