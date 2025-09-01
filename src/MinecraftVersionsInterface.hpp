#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MinecraftVersionsInterface.h"

#include"ProgrammPathMeneger.hpp"

class MinecraftVersionsInterface : public QMainWindow
{
    Q_OBJECT

public:
    MinecraftVersionsInterface(QWidget *parent = nullptr);
    ~MinecraftVersionsInterface();

private slots:

    void ListIndexChanged(int index);
    void DeleteButtonPressed();
    void ClearMods();
    void MakeVersionPressed();
    void UpdateMods();
    void SetVersion();
    void ClearCurrent();

private:

    void PrintLogs(const QString& text);

    void InitFields();

private:
    Ui::MinecraftVersionsInterfaceClass ui;

private:

    ProgrammPathMeneger pMenegr;

};
