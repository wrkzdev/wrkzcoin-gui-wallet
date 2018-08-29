// Copyright (c) 2016 The Karbowanec developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QDialog>

namespace Ui {
class PrivateKeysDialog;
}

namespace WalletGui {

class PrivateKeysDialog : public QDialog {
    Q_OBJECT

public:
    PrivateKeysDialog(const QByteArray& _key, QWidget* _parent);
    void walletClosed();
    ~PrivateKeysDialog();

private:
	QScopedPointer<Ui::PrivateKeysDialog> m_ui;
    Q_SLOT void copyKey();
	QByteArray _Currentkey;
    
};

}
