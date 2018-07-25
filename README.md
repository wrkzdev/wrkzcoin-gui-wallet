### Basic features:
* Generate/Backup/Restore wallet
* Encrypt wallet with password
* Built-in CPU miner with preferred pools
* Embedded/Local and remote blockchain
* Multiple location for remote blockchain
* Restore/display mnemonic phrases wallet from paper wallet (Thanks to https://github.com/seredat/karbowanecwallet/)
* Import/Export keys (not private spending and viewing key)
* Send and list transactions
* Block Explorer (for local blockchain)
* Contact list
* More...

### Recommendation
* We suggest to use our remote blockchain. Default address: wrkz-nodes.wrkz.work
* If you prefer specification location:
`Asia: wrkz-asia.wrkz.work (default port 17856)`
`Europe: wrkz-eu.wrkz.work (default port 17856)`
`US: wrkz-us.wrkz.work (default port 17856)`
* Mnemonic phrases backup, we suggest to use English even though other languages are available.

### Build with Windows
#### Prerequisite
You shall have:
* Microsoft Visual Studio 2017 Community Edition
* CMake 3.12 (Preferably GUI version)
* Boost 1.65  or later (32 or 63 bits depend on your build). You can get the compiled version from https://sourceforge.net/projects/boost/files/boost-binaries/
* Qt 5.10.x (32 or 63 bits depend on your build). If you can not find the binary for MSVC 2017, download 2015 version.
#### Generating project files and compilation
* Download or `git clone https://github.com/wrkzdev/wrkzcoin-gui-wallet`
* Change working directory to  `wrkzcoin-gui-wallet` and `git clone https://github.com/wrkzdev/wrkzcoin cryptonote`
* Launch CMake GUI and select source folder where you store `wrkzcoin-gui-wallet`. Build the binaries shall be `wrkzcoin-gui-wallet/build/`
* Click Configure and select Visual Studio 2017 (64). Fix Qt lib paths and libboost path and re-configure again.
* Click Generate button. CMake will generate WrkzCoin-GUI.sln within `wrkzcoin-gui-wallet/build/`
* Launch `x64 Native Tools Command Prompt for VS 2017` (64 bits) or `x86 Native Tools Command Prompt for VS 2017` (32 bits) and change working directory to `wrkzcoin-gui-wallet/build/`
* In `build` directory, type `MSBuild WrkzCoin-GUI.sln /p:Configuration=Release`
* Wait a while. It will generate `WrkzCoin-GUI.exe` if everything goes fine.
* Qt library is required for `WrkzCoin-GUI.exe`. You shall change working directory to `build/Release` directory where there is the `WrkzCoin-GUI.exe` file, you shall run `c:\Qt\5.10.0\msvc2015\bin\windeployqt WrkzCoin-GUI.exe`. Change the path of where `windeployqt` you installed Qt. Qt necessary dll files will be copied to `Release` directory.
* Complete.

### Build with Linux
[Will write]

### Credit
Thanks to Cryptonote Developers, Bytecoin Developers, Monero Developers, Forknote Project, TurtleCoin Project and specifically to
* https://github.com/turtlecoin/ooze-wallet (based code)
* https://github.com/seredat/karbowanecwallet (Mnemonic features)

### Donation
[Wrkz]: WrkzRNDQDwFCBynKPc459v3LDa1gEGzG3j962tMUBko1fw9xgdaS9mNiGMgA9s1q7hS1Z8SGRVWzcGc 8Sh8xsvfZ6u2wJEtoZB

### Contact us
* Twitter: https://twitter.com/wrkzdev
* Discord: https://chat.wrkz.work
