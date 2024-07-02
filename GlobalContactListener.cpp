#include "GlobalContactListener.h"

void GlobalContactListener::BeginContact(b2Contact* contact)
{
	FixtureData* data = (FixtureData*)contact->GetFixtureA()->GetUserData().pointer;

	if (data && data->listener) {
		data->listener->onBeginContact(contact->GetFixtureB());
	}

	data = (FixtureData*)contact->GetFixtureB()->GetUserData().pointer;

	if (data && data->listener) {
		data->listener->onBeginContact(contact->GetFixtureA());
	}

}

void GlobalContactListener::EndContact(b2Contact* contact)
{
	FixtureData* data = (FixtureData*)contact->GetFixtureA()->GetUserData().pointer;

	if (data && data->listener) {
		data->listener->onEndContact(contact->GetFixtureB());
	}

	data = (FixtureData*)contact->GetFixtureB()->GetUserData().pointer;

	if (data && data->listener) {
		data->listener->onEndContact(contact->GetFixtureA());
	}
}
