#include "credentials_tab.h"
#include "models/forms/user_management_form.h"

namespace meow {
namespace ui {
namespace user_manager {

CredentialsTab::CredentialsTab(models::forms::UserManagementForm *form,
                               QWidget * parent)
    : QWidget(parent)
    , _form(form)
{
    createWidgets();
}

void CredentialsTab::createWidgets()
{
    QGridLayout * mainGridLayout = new QGridLayout();
    int row = 0; // ---------------------------

    _usernameLabel = new QLabel(tr("User name:"));
    mainGridLayout->addWidget(_usernameLabel, row, 0);

    _usernameEdit = new QLineEdit();
    _usernameLabel->setBuddy(_usernameEdit);
    mainGridLayout->addWidget(_usernameEdit, row, 1);

    ++row; // ------------------------

    _hostLabel = new QLabel(tr("From host:"));
    mainGridLayout->addWidget(_hostLabel, row, 0);

    _hostEdit = new QLineEdit();
    _hostLabel->setBuddy(_hostEdit);
    mainGridLayout->addWidget(_hostEdit, row, 1);

    ++row; // -----------------------

    _passwordLabel = new QLabel(tr("Password:"));
    mainGridLayout->addWidget(_passwordLabel, row, 0);

    _passwordEdit = new QLineEdit();
    _passwordLabel->setBuddy(_passwordEdit);
    mainGridLayout->addWidget(_passwordEdit, row, 1);

    ++row; // -----------------------

    _repeatPasswordLabel = new QLabel(tr("Repeat password:"));
    mainGridLayout->addWidget(_repeatPasswordLabel, row, 0);

    _repeatPasswordEdit = new QLineEdit();
    _repeatPasswordLabel->setBuddy(_repeatPasswordEdit);
    mainGridLayout->addWidget(_repeatPasswordEdit, row, 1);

    // --------------------------

    mainGridLayout->setColumnMinimumWidth(0, 100);
    mainGridLayout->setColumnStretch(0, 1);
    mainGridLayout->setColumnStretch(1, 3);
    mainGridLayout->setAlignment(Qt::AlignTop);

    this->setLayout(mainGridLayout);
}

void CredentialsTab::fillDataFromForm()
{
    _usernameLabel->setEnabled(_form->hasUser());
    _hostLabel->setEnabled(_form->hasUser());
    _usernameEdit->setEnabled(_form->hasUser());
    _hostEdit->setEnabled(_form->hasUser());
    _passwordLabel->setEnabled(_form->hasUser());
    _passwordEdit->setEnabled(_form->hasUser());
    _repeatPasswordLabel->setEnabled(_form->hasUser());
    _repeatPasswordEdit->setEnabled(_form->hasUser());

    _usernameEdit->blockSignals(true);
    _usernameEdit->setText(_form->userName());
    _usernameEdit->blockSignals(false);

    _hostEdit->blockSignals(true);
    _hostEdit->setText(_form->userHost());
    _hostEdit->blockSignals(false);
}

} // namespace user_manager
} // namespace ui
} // namespace meow
