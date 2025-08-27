# Ledger Creatachain app
This project contains the Creatachain app for Ledger Nano S, Nano S+, X, Flex and Stax.
- Specs / Documentation
- C++ unit tests
- Zemu tests

# Development

## Preconditions

- Be sure you checkout submodules too:

    ```
    git submodule update --init --recursive
    ```

- Install Docker CE
    - Instructions can be found here: https://docs.docker.com/install/

- Create virtual environment
    ```
   python3 -m venv myvenv
   source myvenv/bin/activate
   ```

- We only officially support Ubuntu. Install the following packages:
   ```
   sudo apt update && sudo apt-get -y install build-essential git wget cmake \
  libssl-dev libgmp-dev autoconf libtool
   ```

- Install `node > v18.0`. We typically recommend using `n`

- You will need python 3 and then run
    ```bash
    make deps
    ```

## How to build ?

> We like clion or vscode but let's have some reproducible command line steps
>

- Building the app itself

    If you installed the what is described above, just run:
    ```bash
    sudo make
    ```

## Running tests

- Running C/C++ tests (x64)

    If you installed the what is described above, just run:
    ```bash
    make cpp_test
    ```

- Running device emulation+integration tests!!

   ```bash
    Use Zemu! Explained below!
    ```

## How to test with Zemu?

Let's go! First install everything:
> At this moment, if you change the app you will need to run `sudo make` before running the test again.

```bash
make zemu_install
```

Then you can run JS tests:

```bash
sudo make zemu_test
```

## Using a real device

**2 - Set a test mnemonic**

Many of our integration tests expect the device to be configured with a known test mnemonic.

- Plug your device while pressing the right button

- Your device will show "Recovery" in the screen

- Double click

- Run `make dev_init`. This will take about 2 minutes. The device will be initialized to:

   ```
   PIN: 5555
   Mnemonic: equip will roof matter pink blind book anxiety banner elbow sun young
   ```

**3 - Add a development certificate**

- Plug your device while pressing the right button

- Your device will show "Recovery" in the screen

- Click both buttons at the same time

- Enter your pin if necessary

- Run `make dev_ca`. The device will receive a development certificate to avoid constant manual confirmations.


### Loading into your development device

The Makefile will build the firmware in a docker container and leave the binary in the correct directory.

- Build

   ```
   sudo make                # Builds the app
   ```

- Upload to a device
   The following command will upload the application to the ledger. _Warning: The application will be deleted before uploading._
   ```
   make load          # Builds and loads the app to the device
   ```
