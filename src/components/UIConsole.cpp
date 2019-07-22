#include "UIConsole.hpp"
#include <GUI/BsGUIInputBox.h>
#include <GUI/BsGUILabel.h>
#include <GUI/BsGUILayoutY.h>
#include <GUI/BsGUIPanel.h>
#include <GUI/BsGUIScrollArea.h>
#include <GUI/BsGUITexture.h>
#include <RTTI/RTTI_UIConsole.hpp>
#include <String/BsString.h>
#include <log/logging.hpp>
#include <original-content/OriginalGameResources.hpp>

namespace REGoth
{
  UIConsole::UIConsole(const bs::HSceneObject& parent, HUIElement parentUiElement)
      : UIElement(parent, parentUiElement, new bs::GUIPanel())
  {
    setName("UIConsole");

    // TODO: Proper back/foreground, does not seem to work for mInputBox at all
    bs::GUIPanel* backgroundPanel = layout().addNewElement<bs::GUIPanel>(1);
    mBackground = backgroundPanel->addNewElement<bs::GUITexture>("GothicConsoleBackground");

    bs::GUIPanel* foregroundPanel = layout().addNewElement<bs::GUIPanel>(0);
    bs::GUILayoutY* layoutY       = foregroundPanel->addNewElement<bs::GUILayoutY>();

    mScrollArea = layoutY->addNewElement<bs::GUIScrollArea>();
    mScrollArea->getLayout().addNewElement<bs::GUILabel>(bs::HString("test"));

    mInputBox = layoutY->addNewElement<bs::GUIInputBox>(false, "GothicConsoleInputBox");
    mInputBox->setText("I am a console!");
  }

  UIConsole::~UIConsole()
  {
  }

  void UIConsole::onInitialized()
  {
    mToggleConsole = bs::VirtualButton("ToggleConsole");
    mConfirm       = bs::VirtualButton("Confirm");
  }

  void UIConsole::update()
  {
    UIElement::update();

    bs::Rect2I parentBounds = parentLayout().getBounds();

    layout().setPosition(0, 0);
    layout().setWidth(parentBounds.width);
    layout().setHeight(parentBounds.height * 0.2);

    // Activation Handling
    if (bs::gVirtualInput().isButtonDown(mToggleConsole))
    {
      mState = (mState == State::Closed) ? State::Open : State::Closed;
    }

    // State handling
    switch (mState)
    {
      case State::Closed:
        mBackground->setVisible(false);
        mScrollArea->setVisible(false);
        mInputBox->setVisible(false);
        mInputBox->setFocus(false);
        break;

      case State::Open:
        mBackground->setVisible(true);
        mScrollArea->setVisible(true);
        mInputBox->setVisible(true);
        mInputBox->setFocus(true);
        break;
    }

    if (mState == State::Open)
    {
      // Input Handling
    }
  }

  bs::String UIConsole::getInput()
  {
    return mInputBox->getText();
  }

  void UIConsole::clearInput()
  {
    mInputBox->setText("");
  }

  void UIConsole::setOutput(bs::Vector<bs::String> outputs)
  {
    for (auto output : outputs)
    {
      setOutput(output);
    }
  }

  void UIConsole::setOutput(bs::String output)
  {
    mScrollArea->getLayout().addNewElement<bs::GUILabel>(bs::HString(output));
  }

  REGOTH_DEFINE_RTTI(UIConsole)
}  // namespace REGoth