# node-native-code-example

Replace any slow function by writing native code in C++. Import and execute it in Node JS.

## Installation

Use the package manager [npm](https://www.npmjs.com/) to install node-gyp.

```bash
nvm use 16
npm install -g node-gyp
```

## Usage

```bash
cd node-native-code-example
node-gyp configure
node-gyp build
node demo.js
```