#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height, std::string title)
{
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);
	this->window->setActive(true);
	this->window->setVerticalSyncEnabled(true);

	this->soundtrack = new Soundtrack();

	appStates = AppStates::START;

	this->states.push_back(new StartState());
	this->states.push_back(new ChoiceState());
	this->states.push_back(new InitState());
	this->states.push_back(new GameState());
	this->states.push_back(new EndState());
	this->states.push_back(new SettingsState());
	this->states.push_back(new VolumeState());
	this->states.push_back(new GoodbyeState());
	for (auto& state : states)
	{
		state->init(this->window);
		state->initMusic(this->soundtrack);
	}
	this->run();
}

void Engine::run()
{
	while (this->window->isOpen())
	{
		if (isOk && appStates == AppStates::GAME_FRIEND)
		{
			reinterpret_cast<GameState*>(this->states[3])->initSets(reinterpret_cast<InitState*>(this->states[2])->getUsers());
			reinterpret_cast<EndState*>(this->states[4])->initSets(reinterpret_cast<InitState*>(this->states[2])->getUsers());
			isOk = false;
		}
		window->clear();
		this->helper = appStates;
		switch (appStates)
		{
		case AppStates::NEW_START:
			this->init();
			isOk = true;
			appStates = AppStates::START;
			break;
		case AppStates::START:
			this->states[0]->handleInput();
			this->window->draw(*this->states[0]);
			break;
		case AppStates::CHOICE:
			this->states[1]->handleInput();
			this->window->draw(*this->states[1]);
			break;
		case AppStates::FRIEND_INIT:
			this->states[2]->handleInput();
			this->window->draw(*this->states[2]);
			break;
		case AppStates::AI_INIT:
			appStates = AppStates::START; // TODO
			break;
		case AppStates::ONLINE_INIT:
			appStates = AppStates::START; // TODO
			break;
		case AppStates::GAME_FRIEND:
			this->states[3]->handleInput();
			this->window->draw(*this->states[3]);
			break;
		case AppStates::WINNER_WND:
			this->states[4]->handleInput();
			this->window->draw(*this->states[4]);
			break;
		case AppStates::VOLUME:
			this->states[6]->handleInput();
			this->window->draw(*this->states[6]);
			break;
		case AppStates::GOODBYE:
			this->states[7]->handleInput();
			this->window->draw(*this->states[7]);
			break;
		case AppStates::SETTINGS:
			this->states[5]->handleInput();
			this->window->draw(*this->states[5]);
			break;
		case AppStates::CLOSE:
			Sleep(100);
		default:
			this->window->close();
			break;
		}
		window->display();
		this->switchState();
	}
}

void Engine::init()
{
	for (auto& state : states)
		delete state;
	this->states[0] = new StartState();
	this->states[1] = new ChoiceState();
	this->states[2] = new InitState();
	this->states[3] = new GameState();
	this->states[4] = new EndState();
	this->states[5] = new SettingsState();
	this->states[6] = new VolumeState();
	this->states[7] = new GoodbyeState();
	for (auto& state : states)
	{
		state->init(this->window);
		state->initMusic(this->soundtrack);
	}
}

void Engine::switchState()
{
	if (this->helper != appStates)
	{
		Sleep(150);
		if (appStates == AppStates::SETTINGS && helper != AppStates::VOLUME && helper != AppStates::GOODBYE)
			reinterpret_cast<SettingsState*>(this->states[5])->setPreviousState(this->helper);
		else if (appStates == AppStates::GOODBYE)
			reinterpret_cast<GoodbyeState*>(this->states[7])->setPreviousState(this->helper);
	}
}

Engine::~Engine()
{
	for (auto state : this->states)
		delete state;
	delete this->window;
	delete this->soundtrack;
}