#!/bin/bash

# Extended xv6 Setup Script
# This script helps set up the development environment for the Extended xv6 OS

set -e  # Exit on any error

echo "🚀 Setting up Extended xv6 Operating System Development Environment"
echo "================================================================"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="Linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]]; then
    OS="Windows"
else
    OS="Unknown"
fi

print_status "Detected OS: $OS"

# Check for required tools
check_tool() {
    if command -v $1 &> /dev/null; then
        print_success "$1 is installed"
        return 0
    else
        print_error "$1 is not installed"
        return 1
    fi
}

print_status "Checking required tools..."

MISSING_TOOLS=()

# Check for make
if ! check_tool make; then
    MISSING_TOOLS+=("make")
fi

# Check for gcc
if ! check_tool gcc; then
    MISSING_TOOLS+=("gcc")
fi

# Check for git
if ! check_tool git; then
    MISSING_TOOLS+=("git")
fi

# Check for QEMU
if ! check_tool qemu-system-i386; then
    if ! check_tool qemu; then
        MISSING_TOOLS+=("qemu")
    fi
fi

# Install missing tools based on OS
if [ ${#MISSING_TOOLS[@]} -ne 0 ]; then
    print_warning "Missing tools: ${MISSING_TOOLS[*]}"
    
    if [ "$OS" = "Linux" ]; then
        print_status "Installing missing tools on Linux..."
        sudo apt-get update
        sudo apt-get install -y build-essential git qemu-system-x86
        
    elif [ "$OS" = "macOS" ]; then
        print_status "Installing missing tools on macOS..."
        if command -v brew &> /dev/null; then
            brew install qemu
        else
            print_error "Homebrew not found. Please install Homebrew first:"
            print_error "https://brew.sh/"
            exit 1
        fi
        
    else
        print_error "Please install the missing tools manually:"
        for tool in "${MISSING_TOOLS[@]}"; do
            print_error "  - $tool"
        done
        exit 1
    fi
fi

# Check for cross-compiler
print_status "Checking for i386 cross-compiler..."

if command -v i386-linux-gnu-gcc &> /dev/null; then
    print_success "i386 cross-compiler found"
elif command -v gcc &> /dev/null; then
    # Check if gcc supports i386
    if gcc -m32 -E -x c /dev/null &> /dev/null; then
        print_success "Native gcc supports i386 target"
    else
        print_warning "Native gcc doesn't support i386 target"
        if [ "$OS" = "Linux" ]; then
            print_status "Installing i386 support..."
            sudo apt-get install -y gcc-multilib gcc-multilib-i386-linux-gnu
        fi
    fi
else
    print_error "No suitable compiler found"
    exit 1
fi

# Create necessary directories if they don't exist
print_status "Setting up project structure..."
mkdir -p kernel user include .github/workflows .github/ISSUE_TEMPLATE

# Make setup script executable
chmod +x setup.sh

print_success "Development environment setup complete!"

# Build instructions
echo ""
echo "📋 Next Steps:"
echo "=============="
echo "1. Build the project:"
echo "   make clean && make"
echo ""
echo "2. Run in QEMU:"
echo "   make qemu"
echo ""
echo "3. Run tests:"
echo "   semtest"
echo "   schedtest"
echo "   swaptest"
echo ""
echo "4. View documentation:"
echo "   cat README.md"
echo ""

print_success "Setup complete! You're ready to build and run Extended xv6."
