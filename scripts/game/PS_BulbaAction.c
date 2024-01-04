class SCR_BulbaAction : SCR_InventoryAction
{	
	int m_iTargetSlotID = -1;
	bool m_bWasUnequipping = false;
	ref SCR_EquipPickedWeapon m_pEquipCB = new SCR_EquipPickedWeapon;
	
	override bool CanBePerformedScript(IEntity user)
 	{
		if ( !super.CanBePerformedScript( user ) )
			return false;
		CharacterControllerComponent controller = CharacterControllerComponent.Cast(user.FindComponent(CharacterControllerComponent));
		
		BaseWeaponManagerComponent baseWeaponManagerComponent = BaseWeaponManagerComponent.Cast(user.FindComponent(BaseWeaponManagerComponent));
		
		if (baseWeaponManagerComponent.GetCurrentWeapon())
			SetCannotPerformReason("Руки заняты");
		
		return controller.CanPlayItemGesture() && !baseWeaponManagerComponent.GetCurrentWeapon();

 	}
	
	override void OnConfirmed(IEntity pUserEntity)
	{
		IEntity pOwnerEntity = m_Item.GetOwner();
		SCR_InventoryStorageManagerComponent manager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		EquipedWeaponStorageComponent weaponStorage = EquipedWeaponStorageComponent.Cast(pUserEntity.FindComponent(EquipedWeaponStorageComponent));

		if (!manager || !weaponStorage)
			return;
		m_pEquipCB.m_pWeapon = pOwnerEntity;
		
		// Double check actual state... By this time slot shouldn't contain any weapon
		if (weaponStorage.GetSlot(m_iTargetSlotID) == null || weaponStorage.GetSlot(m_iTargetSlotID).GetAttachedEntity() != null)
		{
			m_iTargetSlotID = -1;
			return;
		}
		if (manager.TryInsertItemInStorage(pOwnerEntity, weaponStorage, m_iTargetSlotID, m_pEquipCB))
		{
			// Play sound
			manager.PlayItemSound(pOwnerEntity, SCR_SoundEvent.SOUND_EQUIP);
		}
		
		m_iTargetSlotID = -1;
	}
	
	override protected void PerformActionInternal(SCR_InventoryStorageManagerComponent manager, IEntity pOwnerEntity, IEntity pUserEntity)
	{
		CharacterControllerComponent controller = CharacterControllerComponent.Cast(pUserEntity.FindComponent(CharacterControllerComponent));
		if (!controller || controller.IsPlayingGesture())
			return;
		if (m_iTargetSlotID > -1)
			return;
		m_pEquipCB.m_pController = controller;
		EquipedWeaponStorageComponent weaponStorage = EquipedWeaponStorageComponent.Cast(pUserEntity.FindComponent(EquipedWeaponStorageComponent));
		
		BaseWeaponManagerComponent weaponManager = BaseWeaponManagerComponent.Cast(pUserEntity.FindComponent(BaseWeaponManagerComponent));
		
		if (!weaponStorage || !weaponManager)
			return;
		
		WeaponComponent weapon = WeaponComponent.Cast(pOwnerEntity.FindComponent(WeaponComponent));
		WeaponSlotComponent weaponSlotCurr = weaponManager.GetCurrentSlot();
		
		array<WeaponSlotComponent> weaponsList = {};
		int weaponCount = weaponManager.GetWeaponsSlots(weaponsList);
		array<int> suitableSlots = {};
		// Just filtering out suitable slots by weapon type
		for (int i = 0; i < weaponCount; i++)
		{
			WeaponSlotComponent weaponSlot = weaponsList[i];
			string weaponSlotType = weaponSlot.GetWeaponSlotType();
			
			if (weaponSlotType.Compare(weapon.GetWeaponSlotType()) != 0 && !CharacterHandWeaponSlotComponent.Cast(weaponSlot))
			{
				continue;
			}
			suitableSlots.Insert(i);
		}
		
		if (suitableSlots.Count() == 0)
			return;
		
		int i = 0;
		// Let's try to find empty slot and equip weapon to it
		if (suitableSlots.Count() > 1)
		{
			for (int j = 0; j < suitableSlots.Count(); j++)
			{
				WeaponSlotComponent slot = WeaponSlotComponent.Cast(weaponsList[suitableSlots[j]]);
				
				if (slot.GetWeaponEntity() == null)
				{
					i = j;
					break;
				}
				// or fall back to currently equipped
				if (slot == weaponSlotCurr)
				{
					i = j;
				}
			}
		}
		WeaponSlotComponent slot = WeaponSlotComponent.Cast(weaponsList[suitableSlots[i]]);
		
		m_bWasUnequipping = false;
		m_pEquipCB.m_bNoEquipAnims = weaponSlotCurr == null;
		// Free hands, play gesture right away and grab weapon
		// If we are equiping to hand slot, just move it into hand directly
		if (CharacterHandWeaponSlotComponent.Cast(slot))
		{
			if (manager.TryInsertItemInStorage(pOwnerEntity, weaponStorage, slot.GetWeaponSlotIndex()))
			{
				// Play sound
				manager.PlayItemSound(pOwnerEntity, SCR_SoundEvent.SOUND_EQUIP);
			}
		}
		else
		{
			if (controller.TryPlayItemGesture(EItemGesture.EItemGesturePickUp, this, "Character_ActionGrab"))
				m_iTargetSlotID = slot.GetWeaponSlotIndex();
		}
	}
}