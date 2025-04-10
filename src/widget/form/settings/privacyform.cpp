/* SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright © 2014-2019 by The qTox Project Contributors
 * Copyright © 2024-2025 The TokTok team.
 */

#include "privacyform.h"

#include "ui_privacysettings.h"

#include "src/core/core.h"
#include "src/nexus.h"
#include "src/persistence/history.h"
#include "src/persistence/profile.h"
#include "src/persistence/settings.h"
#include "src/widget/form/settingswidget.h"
#include "src/widget/tool/recursivesignalblocker.h"
#include "src/widget/translator.h"
#include "src/widget/widget.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include <chrono>
#include <random>

PrivacyForm::PrivacyForm(Core* core_, Settings& settings_, Style& style, Profile& profile_)
    : GenericForm(QPixmap(":/img/settings/privacy.png"), style)
    , bodyUI(new Ui::PrivacySettings)
    , core{core_}
    , settings{settings_}
    , profile{profile_}
{
    bodyUI->setupUi(this);

    // block all child signals during initialization
    const RecursiveSignalBlocker signalBlocker(this);

    eventsInit();
    Translator::registerHandler([this] { retranslateUi(); }, this);
}

PrivacyForm::~PrivacyForm()
{
    Translator::unregister(this);
    delete bodyUI;
}

void PrivacyForm::on_cbKeepHistory_stateChanged()
{
    settings.setEnableLogging(bodyUI->cbKeepHistory->isChecked());
    if (!bodyUI->cbKeepHistory->isChecked()) {
        emit clearAllReceipts();
        QMessageBox::StandardButton dialogDelHistory;
        dialogDelHistory =
            QMessageBox::question(nullptr, tr("Confirmation"),
                                  tr("Do you want to permanently delete all chat history?"),
                                  QMessageBox::Yes | QMessageBox::No);
        if (dialogDelHistory == QMessageBox::Yes) {
            profile.getHistory()->eraseHistory();
        }
    }
}

void PrivacyForm::on_cbTypingNotification_stateChanged()
{
    settings.setTypingNotification(bodyUI->cbTypingNotification->isChecked());
}

void PrivacyForm::on_nospamLineEdit_editingFinished()
{
    const QString newNospam = bodyUI->nospamLineEdit->text();

    bool ok;
    const uint32_t nospam = newNospam.toLongLong(&ok, 16);
    if (ok) {
        core->setNospam(nospam);
    }
}

void PrivacyForm::showEvent(QShowEvent* event)
{
    std::ignore = event;
    const Settings& s = settings;
    bodyUI->nospamLineEdit->setText(core->getSelfId().getNoSpamString());
    bodyUI->cbTypingNotification->setChecked(s.getTypingNotification());
    bodyUI->cbKeepHistory->setChecked(settings.getEnableLogging());
    bodyUI->blockListTextEdit->setText(s.getBlockList().join('\n'));
}

void PrivacyForm::on_randomNospamButton_clicked()
{
    uint32_t newNospam{0};

    static std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    newNospam = rng();

    core->setNospam(newNospam);
    bodyUI->nospamLineEdit->setText(core->getSelfId().getNoSpamString());
}

void PrivacyForm::on_nospamLineEdit_textChanged()
{
    QString str = bodyUI->nospamLineEdit->text();
    const int curs = bodyUI->nospamLineEdit->cursorPosition();
    if (str.length() != 8) {
        str = QString("00000000").replace(0, str.length(), str);
        bodyUI->nospamLineEdit->setText(str);
        bodyUI->nospamLineEdit->setCursorPosition(curs);
    }
}

void PrivacyForm::on_blockListTextEdit_textChanged()
{
    const QStringList strlist = bodyUI->blockListTextEdit->toPlainText().split('\n');
    settings.setBlockList(strlist);
}

void PrivacyForm::retranslateUi()
{
    bodyUI->retranslateUi(this);
}
