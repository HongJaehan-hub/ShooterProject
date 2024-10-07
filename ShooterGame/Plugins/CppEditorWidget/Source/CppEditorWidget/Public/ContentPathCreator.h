// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "ContentPathCreator.generated.h"

/**
 * 
 */
UCLASS()
class CPPEDITORWIDGET_API UContentPathCreator : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
public:
	UContentPathCreator();
	void NativeConstruct() override;
	
	UFUNCTION()
	void OnCreateButtonClicked();

public:
	UPROPERTY(Meta = (BindWidget))
	class UButton* CreateButton;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* FilePathTextBox;

private:
	void CreateUserWidgetContentPath();
};
