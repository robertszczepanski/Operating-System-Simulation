#include "ProcessesManagementState.h"

void ProcessesManagementState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->texture.loadFromFile("Resources/images/MMBackground.png");
	this->background.setTexture(&texture);

	this->menutexture.loadFromFile("Resources/Images/menu.png");
	this->menu1.setSize(sf::Vector2f(256.f, 349.f));
	this->menu1.setTexture(&menutexture);
	this->menu1.setPosition(sf::Vector2f(120.f, 200.f));
	this->menu2.setSize(sf::Vector2f(256.f, 349.f));
	this->menu2.setTexture(&menutexture);
	this->menu2.setPosition(sf::Vector2f(370.f, 200.f));
	this->menu3.setSize(sf::Vector2f(256.f, 349.f));
	this->menu3.setTexture(&menutexture);
	this->menu3.setPosition(sf::Vector2f(620.f, 200.f));
}

void ProcessesManagementState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AppleGaramond.ttf"))
	{
		throw("ERROR:could not load font");
	}
}

void ProcessesManagementState::initButtons()
{
	this->buttons["HELP"] = new Button(900, 0, 29, 50, &this->font, "", "Resources/Images/help.png", "Resources/Images/helpMoused.png", "Resources/Images/helpClicked.png");
	this->buttons["EXIT"] = new Button(950, 0, 44, 50, &this->font, "", "Resources/Images/quit.png", "Resources/Images/quitHover.png", "Resources/Images/quitHover.png");
	this->buttons["STEP"] = new Button(457, 700, 85, 85, &this->font, "", "Resources/Images/step.png", "Resources/Images/stepHover.png", "Resources/Images/stepClicked.png");

	this->buttons["LOGO"] = new Button(0, 300, 127, 151, &this->font, "", "Resources/Images/logo.png", "Resources/Images/logoHover.png", "Resources/Images/logoClicked.png");

	this->buttons["PROGRAMS"] = new Button(130, 250, 244, 44, &this->font, "Programs");
	this->buttons["FILE_MANAGER"] = new Button(130, 350, 244, 44, &this->font, "File manager");
	this->buttons["CONTROL_PANEL"] = new Button(130, 450, 244, 44, &this->font, "Control panel");

	this->buttons["VM"] = new Button(380, 230, 244, 44, &this->font, "VM");
	this->buttons["RAM"] = new Button(380, 280, 244, 44, &this->font, "RAM");
	this->buttons["DISC"] = new Button(380, 330, 244, 44, &this->font, "Disc");
	this->buttons["PROCSCHE"] = new Button(380, 380, 244, 44, &this->font, "Process scheduling");
	this->buttons["COMMUNICATION"] = new Button(380, 430, 244, 44, &this->font, "Communication");
	this->buttons["PROCMANA"] = new Button(380, 480, 244, 44, &this->font, "Processes management");

	this->buttons["PCB"] = new Button(630, 230, 244, 44, &this->font, "PCB");
	this->buttons["READYQUEUE"] = new Button(630, 310, 244, 44, &this->font, "Ready queue");
	this->buttons["MAP"] = new Button(630, 390, 244, 44, &this->font, "Map");
	this->buttons["SEM"] = new Button(630, 460, 244, 44, &this->font, "Semaphore queue");
}

ProcessesManagementState::ProcessesManagementState(sf::RenderWindow *window, std::stack<GUIState*> *states, sf::Event *event)
	:GUIState(window, states, event)
{
	this->initFonts();
	this->initButtons();
	this->initBackground();
}

ProcessesManagementState::~ProcessesManagementState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void ProcessesManagementState::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void ProcessesManagementState::update(const float& dt)
{
	if (event->type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->updateTimebar();
	this->updateButtons();

}

void ProcessesManagementState::updateButtons()
{
	//updating buttons and does all funcionality
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["LOGO"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["PROGRAMS"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["CONTROL_PANEL"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["FILE_MANAGER"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["HELP"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new HelpState(this->window, this->states, this->event));
	}

	if (this->buttons["VM"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["RAM"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["DISC"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["PROCSCHE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["COMMUNICATION"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["PROCMANA"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->pop();
	}

	if (this->buttons["PCB"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new PCBInput(this->window, this->states, this->event));

	}

	if (this->buttons["READYQUEUE"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		PCB::printReadyQueue();
	}

	if (this->buttons["MAP"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		PCB::printMap();
	}

	if (this->buttons["SEM"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		this->states->push(new PCBSemInput(this->window, this->states, this->event));
	}

	if (this->buttons["STEP"]->isPressed() && isMousePressed == false)
	{
		isMousePressed = true;
		System::CPU.nextStep();
	}

	//Quiting shell
	if (this->buttons["EXIT"]->isPressed() && isMousePressed == false)
	{
		this->window->close();
	}

}

void ProcessesManagementState::updateTimebar()
{
	this->timebar.getActualTime();
}

void ProcessesManagementState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}

void ProcessesManagementState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->menu1);
	target->draw(this->menu2);
	target->draw(this->menu3);
	this->timebar.render(target);
	this->renderButtons(target);

	//Only for tests, remove later
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(16);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
