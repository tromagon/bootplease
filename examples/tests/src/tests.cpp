#include "tests.h"
#include "Easing.h"

#include <iostream>

using namespace std;

const char* ExampleEvent::INIT = "ExampleEvent_INIT";
const char* ExampleEvent::COMPLETE = "ExampleEvent_COMPLETE";
const char* ExampleEvent::SECOND_COMPLETE = "ExampleEvent_SECOND_COMPLETE";

const char* InjectionID::MODEL_A = "InjectionID_MODEL_A";
const char* InjectionID::MODEL_B = "InjectionID_MODEL_B";
const char* InjectionID::MODEL_A_2 = "InjectionID_MODEL_A_2";

EventDispatcherTest::EventDispatcherTest()
{
	cout << "----------- Start EventDispatcher Test" << endl;

	dispatcher = new EventDispatcher();
	int i = dispatcher->AddListener(ExampleEvent::INIT, &EventDispatcherTest::hello, *this);
	dispatcher->AddListener(ExampleEvent::INIT, &EventDispatcherTest::hello2, *this);
	ExampleEvent evt(ExampleEvent::INIT);
	dispatcher->Dispatch(evt);
	dispatcher->RemoveListener(i);
	dispatcher->RemoveListener(ExampleEvent::INIT, &EventDispatcherTest::hello2, *this);
	dispatcher->Dispatch(evt);

	cout << "----------- End EventDispatcher Test" << endl;
}

EventDispatcherTest::~EventDispatcherTest()
{
	delete dispatcher;
}

void EventDispatcherTest::hello(Event& evt)
{
	std::cout << "Hello " << evt.GetType() << std::endl;
}

void EventDispatcherTest::hello2(Event& evt)
{
	std::cout << "Hello2 " << evt.GetType() << std::endl;
}

SequenceTest::SequenceTest()
{
	cout << "----------- Start SequenceTest Test" << endl;

	dispatcher = new EventDispatcher();
	dispatcher->AddListener(ExampleEvent::INIT, &SequenceTest::onInit, *this);

	sequence = new Sequence(*dispatcher);
	sequence->AddListener(SequenceEvent::STARTED, &SequenceTest::onSequenceStarted, *this);
	sequence->AddListener(SequenceEvent::STEP_COMPLETE, &SequenceTest::onSequenceStepComplete, *this);
	sequence->AddListener(SequenceEvent::COMPLETE, &SequenceTest::onSequenceComplete, *this);

	sequence->Call(&SequenceTest::methodA, *this);
	ExampleEvent evt(ExampleEvent::INIT);
	sequence->Dispatch(evt);
	sequence->WaitFor(ExampleEvent::COMPLETE, &SequenceTest::onComplete, *this);
	sequence->WaitFor(ExampleEvent::SECOND_COMPLETE);
	sequence->Dispatch(evt);
	sequence->WaitFor(ExampleEvent::COMPLETE);
	sequence->WaitFor(ExampleEvent::SECOND_COMPLETE);
	Params p(4, 6);
	sequence->Call(&SequenceTest::methodB, *this, p);
	sequence->Start();

	/*ExampleEvent evt(ExampleEvent::INIT);
	sequence->Dispatch(evt);
	sequence->WaitFor(ExampleEvent::COMPLETE, &SequenceTest::onComplete, *this);
	sequence->Start();*/

	cout << "----------- End SequenceTest Test" << endl;
}

SequenceTest::~SequenceTest()
{
	delete sequence;
	delete dispatcher;
}

void SequenceTest::methodA()
{
	cout << "MethodA" << endl;
}

void SequenceTest::methodB(Params& params)
{
	cout << "methodB : x=" << params.m_X << ", y=" << params.m_Y << endl;
}

void SequenceTest::onInit(Event& evt)
{
	cout << "onInit() " << evt.GetType() << endl;

	ExampleEvent completeEvent(ExampleEvent::COMPLETE);
	dispatcher->Dispatch(completeEvent);

	ExampleEvent secondCompleteEvent(ExampleEvent::SECOND_COMPLETE);
	dispatcher->Dispatch(secondCompleteEvent);
}

void SequenceTest::onComplete(Event& evt)
{
	cout << "onComplete() " << evt.GetType() << endl;
}

void SequenceTest::onSequenceStarted(Event& evt)
{
	sequence->RemoveListener(SequenceEvent::STARTED, &SequenceTest::onSequenceStarted, *this);
	cout << "Sequence has started" << endl;
}

void SequenceTest::onSequenceStepComplete(Event& evt)
{
	SequenceEvent& seqEvt = static_cast<SequenceEvent&>(evt);
	sequence->RemoveListener(SequenceEvent::STEP_COMPLETE, &SequenceTest::onSequenceStarted, *this);
	cout << "Sequence Step is complete" << endl;
}

void SequenceTest::onSequenceComplete(Event& evt)
{
	SequenceEvent& seqEvt = static_cast<SequenceEvent&>(evt);
	seqEvt.GetSequence().RemoveListener(SequenceEvent::COMPLETE, &SequenceTest::onSequenceComplete, *this);

	dispatcher->RemoveListener(ExampleEvent::INIT, &SequenceTest::onInit, *this);

	cout << "Sequence is complete" << endl;
}

InjectionTest::InjectionTest()
{
	cout << "----------- Start InjectionTest Test" << endl;

	ModelA* modelA = new ModelA();
	ModelB* modelB = new ModelB();

	injector.Map(modelA, InjectionID::MODEL_A);
	injector.Map(modelB, InjectionID::MODEL_B);

	if (injector.GetInstanceById<ModelA>(InjectionID::MODEL_A))
	{
		cout << "Model A found in injector" << endl; 
	}

	injector.UnMap(modelA);

	if (!injector.GetInstanceById<ModelA>(InjectionID::MODEL_A))
	{
		cout << "Model A removed from injector" << endl;
	}

	injector.UnMap(InjectionID::MODEL_B);

	if (!injector.GetInstanceById<ModelB>(InjectionID::MODEL_B))
	{
		cout << "Model B removed from injector" << endl;
	}

	delete modelA;
	delete modelB;

	cout << "----------- End InjectionTest Test" << endl;
}

CommandMapTest::CommandMapTest()
{
	cout << "----------- Start CommandMapTest Test" << endl;

	Injector injector;
	ModelA* modelA = new ModelA();
	injector.Map(modelA, InjectionID::MODEL_A);

	EventDispatcher dispatcher;
	CommandMap commandMap(dispatcher);
	CommandFactory commandFactory;

	injector.SetCommandMap(commandMap);

	commandMap.Map(ExampleEvent::INIT, &CommandFactory::GetExampleCommandA, commandFactory);
	commandMap.Map(ExampleEvent::INIT, &CommandFactory::GetExampleCommandB, commandFactory);

	ExampleEvent evt(ExampleEvent::INIT);
	dispatcher.Dispatch(evt);

	ExampleEvent completeEvt(ExampleEvent::COMPLETE);
	dispatcher.Dispatch(completeEvt);

	commandMap.UnMap(ExampleEvent::INIT, &CommandFactory::GetExampleCommandA, commandFactory);
	commandMap.UnMap(ExampleEvent::INIT, &CommandFactory::GetExampleCommandB, commandFactory);

	cout << "----------- End CommandMapTest Test" << endl;
}

void ExampleCommandA::execute()
{
	cout << "ExampleCommandA is executing with event " << GetEvent().GetType() << endl;

	if (GetInjector().GetInstanceById<ModelA>(InjectionID::MODEL_A))
	{
		cout << "Model A found in injector" << endl; 
	}
}

void ExampleCommandB::execute()
{
	cout << "ExampleCommandB is executing with event " << GetEvent().GetType() << endl;

	GetCommandMap().Detain(*this);

	AddContextListener(ExampleEvent::COMPLETE, &ExampleCommandB::onEvent, *this);
}

void ExampleCommandB::onEvent(Event& evt)
{
	RemoveContextListener(ExampleEvent::COMPLETE, &ExampleCommandB::onEvent, *this);

	cout << "ExampleCommandB is releasing" << endl;

	GetCommandMap().Release(*this);
}

TweenTest::TweenTest()
{
	tweenManager = new TweenManager();
	display = new IDisplay();

	TweenX& tweenX = tweenManager->CreateTween<TweenX>(*display);
	tweenX.AddListener(TweenEvent::START, &TweenTest::onTweenStart, *this);

	tweenX
		.From(0).To(60).Duration(3.0f)
		.Delay(1.0f)
		.Easing(Linear::EaseNone)
		.OnComplete(&TweenTest::onTweenComplete, *this)
		.OnUpdate(&TweenTest::onTweenUpdate, *this)
		.Play();

	//tween.Stop();

	/*Timeline timeline = new Timeline();
	timeline.AddEventListener(TimelineEvent::PLAY, onStart);
	timeline.AddEventListener(TimelineEvent::STOP, onStop);
	timeline.AddEventListener(TimelineEvent::COMPLETE, onComplete);

	timeline.insert(new Tween(display, 0.3, TweenX.from(0).to(100), ease), 0.2);
	timeline.insert(new Tween(display, 0.3, TweenY.from(0).to(100), ease), 0.2);

	tween.play();*/
}

TweenTest::~TweenTest()
{
	delete tweenManager;
	delete display;
}

void TweenTest::onTweenStart(Event& evt)
{
	
}

void TweenTest::onTweenUpdate(Event& evt)
{
	
}

void TweenTest::onTweenComplete(Event& evt)
{
	
}

void TweenTest::Update(float deltaTime)
{
	tweenManager->Update(deltaTime);

	cout << display->GetX() << endl;
}

Tests::Tests()
{
	EventDispatcherTest* test1 = new EventDispatcherTest();
	delete test1;

	SequenceTest* test2 = new SequenceTest();
	delete test2;

	InjectionTest* test3 = new InjectionTest();
	delete test3;

	CommandMapTest* test4 = new CommandMapTest();
	delete test4;

	test5 = new TweenTest();
}

Tests::~Tests()
{
	delete test5;
}

void Tests::Update(float deltaTime)
{
	test5->Update(deltaTime);
}