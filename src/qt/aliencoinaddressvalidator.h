// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ALIENCOIN_QT_ALIENCOINADDRESSVALIDATOR_H
#define ALIENCOIN_QT_ALIENCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AliencoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AliencoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Aliencoin address widget validator, checks for a valid aliencoin address.
 */
class AliencoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AliencoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ALIENCOIN_QT_ALIENCOINADDRESSVALIDATOR_H
