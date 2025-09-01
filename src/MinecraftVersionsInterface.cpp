#include "MinecraftVersionsInterface.hpp"

#include<iostream>

MinecraftVersionsInterface::MinecraftVersionsInterface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.VersionsList, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MinecraftVersionsInterface::ListIndexChanged);
    connect(ui.DeleteVersion,   &QPushButton::pressed, this, &MinecraftVersionsInterface::DeleteButtonPressed);
    connect(ui.ClearMods,       &QPushButton::pressed, this, &MinecraftVersionsInterface::ClearMods);
    connect(ui.MakeVersion,     &QPushButton::pressed, this, &MinecraftVersionsInterface::MakeVersionPressed);
    connect(ui.UpdateModsB,     &QPushButton::pressed, this, &MinecraftVersionsInterface::UpdateMods);
    connect(ui.SetVersion,      &QPushButton::pressed, this, &MinecraftVersionsInterface::SetVersion);
    connect(ui.ClearCurentMod,  &QPushButton::pressed, this, &MinecraftVersionsInterface::ClearCurrent);

    InitFields();

    auto mineVersions = pMenegr.getMinecraftVersions();
    for (const auto& vers : mineVersions)
        ui.InputVersion->addItem(vers.c_str());
}

MinecraftVersionsInterface::~MinecraftVersionsInterface()
{}


void MinecraftVersionsInterface::PrintLogs(const QString& text)
{
    ui.TextLogs->setText(ui.TextLogs->toPlainText() + text + "\n");
}

void MinecraftVersionsInterface::InitFields()
{
    ui.VersionsList->clear();

    ui.CurrentMineVersion->setText(pMenegr.getCurrentVersion().c_str());
    ui.CurrentVersionName->setText(pMenegr.getCurrentName().c_str());
    auto versions = pMenegr.getVersionNames();
    for (const auto& vers : versions)
        ui.VersionsList->addItem(vers.c_str());
}



void MinecraftVersionsInterface::ListIndexChanged(int index)
{
    auto info = pMenegr.getVersionAtIndex(index);

    ui.CurrentMineVersion_2->setText(info.version.c_str());
    ui.CurrentVersionName_2->setText(info.name.c_str());
}

void MinecraftVersionsInterface::DeleteButtonPressed()
{
    pMenegr.deleteVersionAtIndex(ui.VersionsList->currentIndex());
    
    InitFields();

    PrintLogs("Версия успешно удалена.");
}

void MinecraftVersionsInterface::ClearMods()
{
    pMenegr.clearPaths();
    
    InitFields();

    PrintLogs("Моды успешно отчищены.");
}

void MinecraftVersionsInterface::MakeVersionPressed()
{
    if (ui.InputName->toPlainText().toStdString() == NONE_INFO || ui.InputName->toPlainText().toStdString().size() == 0)
    {
        PrintLogs("Имя не может быть неопределено!");
        return;
    }
    if (pMenegr.haveVersionName(ui.InputName->toPlainText().toStdString()))
    {
        PrintLogs("Такое имя уже существует! Имя версии должно быть уникально!");
        return;
    }
    pMenegr.createVersion(ui.InputName->toPlainText().toStdString(), ui.InputVersion->currentText().toStdString());
    InitFields();
    PrintLogs("Версия создана!");
}

void MinecraftVersionsInterface::UpdateMods()
{
    if (ui.CurrentVersionName->text() == NONE_INFO || ui.CurrentVersionName->text().size() == 0)
    {
        PrintLogs("Имя не может быть неопределено!");
        return;
    }
    

    pMenegr.updateCurrent();
    PrintLogs("Моды и конфиги сохранены");
}

void MinecraftVersionsInterface::SetVersion()
{
    pMenegr.setVersionAt(ui.VersionsList->currentIndex());
    InitFields();
    PrintLogs("Версия успешно загружена.");
}

void MinecraftVersionsInterface::ClearCurrent()
{
    pMenegr.clearCurrent();
}