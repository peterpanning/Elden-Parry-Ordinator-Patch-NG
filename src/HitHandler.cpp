#include "../include/RE/B/BSTEvent.h"
#include "../include/SKSE/Events.h"
#include "RE/M/Misc.h"

class HitHandler : public RE::BSTEventSink<RE::TESHitEvent>
{

public: 
	static HitHandler* GetSingleton()
	{
		static HitHandler singleton;
		return &singleton;
	}

protected:
	using EventResult = RE::BSEventNotifyControl;

	EventResult ProcessEvent(const RE::TESHitEvent* event, RE::BSTEventSource<RE::TESHitEvent>*) override
	{
		// Dispel Deliverance if the player is hit
		const auto player = RE::PlayerCharacter::GetSingleton();
		if (event->target->AsReference() == player && event->flags.get() != RE::TESHitEvent::Flag::kHitBlocked) {
			const auto deliverance = RE::BGSPerk::LookupByEditorID("ORD_Bck90_Deliverance_Perk_90_OrdASISExclude")->As<RE::BGSPerk>();
			if (player->HasPerk(deliverance)) {
				const auto deliverance = RE::TESForm::LookupByEditorID<RE::MagicItem>("ORD_Bck_Deliverance_Spell_Proc");
				if (player->HasMagicEffect(deliverance->effects[0]->baseEffect)) {
					auto activeEffects = player->GetActiveEffectList();
					for (const auto& effect : *activeEffects) {
						if (effect->spell == deliverance)
							effect->Dispel(true);
					}
				}
			}
		}
		return EventResult::kContinue;
	}

private: 
	private:
	HitHandler() = default;
	HitHandler(const HitHandler&) = delete;
	HitHandler(HitHandler&&) = delete;
	~HitHandler() override = default;
	HitHandler& operator=(const HitHandler&) = delete;
	HitHandler& operator=(HitHandler&&) = delete;
};
