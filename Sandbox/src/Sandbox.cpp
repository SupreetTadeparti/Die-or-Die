#include <Moon.h>

struct Projectile
{
	Double Speed;
	Moon::Material* Material;
	
	Projectile(Double s, Moon::Material* m) : Speed(s), Material(m)
	{
	}
};

struct Weapon
{
	Double Health;
	Double Damage;
	Bool Projectile;
	struct Projectile* projectile;
	Moon::Material* Material;

	Weapon(Double h, Double d, Bool p, Moon::Material* m, struct Projectile* pr=nullptr) : Health(h), Damage(d), Projectile(p), Material(m), projectile(pr)
	{
	}
};

class Sandbox : public Moon::Application
{
public:
	Sandbox() : playerSpeed(0.35), playerX(-width/ 2), level(3), silverDieHovering(false), goldDieHovering(false), silverDieTimeout(100), goldDieTimeout(100), currPlayerMaterial(1), currSilverDieMaterial(0), currGoldDieMaterial(0), oneDown(false), twoDown(false), mainMenu(true), currPlayerAnimationFrame(0),
		playerFacingLeft(false), jumping(false), jumpVelocity(0), jumpTime(300), jumpSpeed(0.6), playerHealth(100), healthVal(100), gameOver(false), playerWeaponX(0), currWeapon(nullptr), freeze(false), weaponless(false), currWeaponIndex(3)
	{
		Moon::Window::SetDimensions((Uint)width, (Uint)height);
		Moon::Window::SetBackgroundColor(165, 42, 42);
		Moon::Window::SetTitle("Do Not Die");
	}

	void OnStart()
	{
		camera = new Moon::Camera();

		gameOverShader = Moon::Shader::GenerateDefaultTexture();
		fixedShader = Moon::Shader::GenerateDefaultTexture();
		colorShader = Moon::Shader::GenerateDefaultColor();
		playerShader = Moon::Shader::GenerateDefaultTexture();
		worldShader = Moon::Shader::GenerateDefaultTexture();

		LoadMaterials();

		gameOverRect = Moon::Models::Rect("A", gameOverShader, 1, 1);
		fixedRect = Moon::Models::Rect("E", fixedShader, 1, 1);
		colorRect = Moon::Models::Rect("D", colorShader, 1, 1);
		playerRect = Moon::Models::Rect("B", playerShader, 1, 1);
		worldRect = Moon::Models::Rect("C", worldShader, 1, 1);

		InitMainMenu();
	}

	void OnUpdate()
	{
		if (mainMenu || gameOver) return;

		if (attack)
		{
			if (playerWeaponX > 20)
			{
				attack = false;
				playerWeaponX = 0;
			}
			else if (playerWeaponX > 10)
			{
				if (playerFacingLeft)
				{
					playerWeapon->Translate(Vec3(1.0, 0, 0));
				}
				else
				{
					playerWeapon->Translate(Vec3(-1.0, 0, 0));
				}
			}
			else
			{
				if (playerFacingLeft)
				{
					playerWeapon->Translate(Vec3(-1.0, 0, 0));
				}
				else
				{
					playerWeapon->Translate(Vec3(1.0, 0, 0));
				}
			}
			playerWeaponX += 0.1;
		}

		if (!freeze)
		{
			for (Moon::Entity* enemy : enemies)
			{
				if (level == 3)
				{
					if (enemy->GetTranslation().x - (playerX + width) > 0)
					{
						enemy->Translate(Vec3(-0.1, 0, 0));
						enemy->Rotate(Vec3(0, 0, 0.01));
					}
					else if (enemy->GetTranslation().x - (playerX + width) < 0)
					{
						enemy->Translate(Vec3(0.1, 0, 0));
						enemy->Rotate(Vec3(0, 0, -0.01));
					}
				}
			}
		}

		if (!attack)
		{
			if (Moon::EventHandler::KeyDown("a") || Moon::EventHandler::KeyDown("LEFT"))
			{
				if (!playerFacingLeft)
				{
					playerWeapon->Scale(Vec3(-128, 0, 0));
					playerWeapon->Translate(Vec3(-120, 0, 0));
				}
				playerFacingLeft = true;
				if (playerX - playerSpeed > leftBorder)
				{
					camera->Move(Vec3(-playerSpeed, 0, 0));
					playerX -= playerSpeed;
				}
				if (++currPlayerAnimationFrame == 100)
				{
					Uint index = currPlayerMaterial;
					if (currPlayerMaterial == 3) index = 1;
					player->SetMaterial(playerMaterials[index + 3]);
					if (++currPlayerMaterial > 3) currPlayerMaterial = 0;
					currPlayerAnimationFrame = 0;
				}
			}

			if (Moon::EventHandler::KeyDown("d") || Moon::EventHandler::KeyDown("RIGHT"))
			{
				if (playerFacingLeft)
				{
					playerWeapon->Scale(Vec3(128, 0, 0));
					playerWeapon->Translate(Vec3(120, 0, 0));
				}
				playerFacingLeft = false;
				if (playerX + playerSpeed < rightBorder)
				{
					camera->Move(Vec3(playerSpeed, 0, 0));
					playerX += playerSpeed;
				}
				if (++currPlayerAnimationFrame == 100)
				{
					Uint index = currPlayerMaterial;
					if (currPlayerMaterial == 3) index = 1;
					player->SetMaterial(playerMaterials[index]);
					if (++currPlayerMaterial > 3) currPlayerMaterial = 0;
					currPlayerAnimationFrame = 0;
				}
			}
		}

		if (!(Moon::EventHandler::KeyDown("a") || Moon::EventHandler::KeyDown("LEFT") || Moon::EventHandler::KeyDown("d") || Moon::EventHandler::KeyDown("RIGHT")))
		{
			player->SetMaterial(playerMaterials[(playerFacingLeft ? 4 : 1)]);
		}

		if (Moon::EventHandler::KeyDown(" "))
		{
			if (!jumping)
			{
				jumpVelocity = jumpSpeed;
				Moon::CustomEvent* fall = new Moon::CustomEvent(FallCallback, jumpTime, this, true);
				Moon::EventHandler::Push(fall);
				jumping = true;
			}
		}

		player->Translate(Vec3(0, jumpVelocity, 0));

		if (Moon::EventHandler::KeyDown("1"))
		{
			if (!oneDown)
			{
				if (silverDieTimeout == 100)
				{
					Moon::CustomEvent* silverDieRoll = new Moon::CustomEvent(OnSilverDieRoll, silverDieTimeout, this, true);
					Moon::EventHandler::Push(silverDieRoll);
				}
			}
			oneDown = true;
		}
		else
		{
			oneDown = false;
		}

		if (Moon::EventHandler::KeyDown("2"))
		{
			if (!twoDown)
			{
				if (goldDieTimeout == 100)
				{
					Moon::CustomEvent* goldDieRoll = new Moon::CustomEvent(OnGoldDieRoll, goldDieTimeout, this, true);
					Moon::EventHandler::Push(goldDieRoll);
				}
			}
			twoDown = true;
		}
		else
		{
			twoDown = false;
		}

		for (Moon::Entity* cloud : clouds)
		{
			cloud->Translate(Vec3(-0.03f, 0, 0));
		}

		worldShader->SetUniformMat4("u_View", camera->GetViewMatrix());
	}

	void LoadMaterials()
	{
		for (Uint i = 1; i <= 8; i++)
		{
			Moon::Texture* cloudTexture = new Moon::Texture("cloud-" + std::to_string(i) + ".png");
			Moon::Material* cloudMaterial = new Moon::Material(Moon::MaterialType::Texture, cloudTexture);
			cloudMaterials.push_back(cloudMaterial);
			if (i > 6) continue;
			Moon::Texture* silverTexture = new Moon::Texture("silver-" + std::to_string(i) + ".png");
			Moon::Material* silverMaterial = new Moon::Material(Moon::MaterialType::Texture, silverTexture);
			silverDieMaterials.push_back(silverMaterial);
			Moon::Texture* goldTexture = new Moon::Texture("gold-" + std::to_string(i) + ".png");
			Moon::Material* goldMaterial = new Moon::Material(Moon::MaterialType::Texture, goldTexture);
			goldDieMaterials.push_back(goldMaterial);
			Moon::Texture* weaponTexture = new Moon::Texture("weapon-" + std::to_string(i) + ".png");
			Moon::Material* weaponMaterial = new Moon::Material(Moon::MaterialType::Texture, weaponTexture);
			weaponMaterials.push_back(weaponMaterial);
			Moon::Texture* playerTexture = new Moon::Texture("player-" + std::to_string(i) + ".png");
			playerMaterials.push_back(new Moon::Material(Moon::MaterialType::Texture, playerTexture));
			if (i > 2) continue;
			Moon::Texture* boulderTexture = new Moon::Texture("boulder-" + std::to_string(i) + ".png");
			boulderMaterials.push_back(new Moon::Material(Moon::MaterialType::Texture, boulderTexture));
		}
		weapons.push_back(new Weapon(10, 1, false, weaponMaterials[0]));
		weapons.push_back(new Weapon(20, 3, false, weaponMaterials[1]));
		weapons.push_back(new Weapon(30, 5, true, weaponMaterials[2]));
		weapons.push_back(new Weapon(40, 8, false, weaponMaterials[3]));
		weapons.push_back(new Weapon(50, 10, true, weaponMaterials[4]));
		weapons.push_back(new Weapon(60, 12, true, weaponMaterials[5]));
		currWeapon = weapons[currWeaponIndex];
		Moon::Texture* gameOverTexture = new Moon::Texture("gameover.png");
		gameOverMaterial = new Moon::Material(Moon::MaterialType::Texture, gameOverTexture);
		Moon::Texture* easyButtonTexture = new Moon::Texture("easy-btn.png");
		buttonMaterials.push_back(new Moon::Material(Moon::MaterialType::Texture, easyButtonTexture));
		Moon::Texture* mediumButtonTexture = new Moon::Texture("medium-btn.png");
		buttonMaterials.push_back(new Moon::Material(Moon::MaterialType::Texture, mediumButtonTexture));
		Moon::Texture* hardButtonTexture = new Moon::Texture("hard-btn.png");
		buttonMaterials.push_back(new Moon::Material(Moon::MaterialType::Texture, hardButtonTexture));
		Moon::Texture* logoTexture = new Moon::Texture("logo.png");
		logoMaterial = new Moon::Material(Moon::MaterialType::Texture, logoTexture);
		Moon::Texture* groundTexture = new Moon::Texture("ground.png");
		groundMaterial = new Moon::Material(Moon::MaterialType::Texture, groundTexture);
	}

	void InitMainMenu()
	{
		for (Uint i = 0; i < 3; i++)
		{
			Vec3 btnPosition = Vec3(width / 2 + 2, height / 2 - i * 70, 0);
			buttonPositions.push_back(btnPosition);
			buttonHoverings.push_back(false);
			Moon::Entity* button = new Moon::Entity(fixedRect, btnPosition, Vec3(), Vec3(128, 64, 1));
			button->SetMaterial(buttonMaterials[i]);
			buttons.push_back(button);
			Moon::Renderer::AddEntity(button);
		}
		Vec3 logoPosition = Vec3(width / 2, height - 100, 0);
		logo = new Moon::Entity(fixedRect, logoPosition, Vec3(), Vec3(512, 128, 1));
		logo->SetMaterial(logoMaterial);
		Moon::Renderer::AddEntity(logo);
		Moon::EventHandler::OnClick(ClickCallback, this);
		Moon::EventHandler::OnMouseMove(MouseMoveCallback, this);
	}

	void InitGame()
	{
		mainMenu = false;

		for (Uint i = 0; i < 3; i++)
		{
			Moon::Renderer::RemoveEntity(buttons[i]);
		}
		Moon::Renderer::RemoveEntity(logo);

		Moon::Texture* backgroundTexture = nullptr;

		if (level == 1)
		{
			enemyHealth = 5;
			audioDuration = 41;
			backgroundTexture = new Moon::Texture("easy-background.png");
			Moon::Texture* enemyTexture1 = new Moon::Texture("easy-enemy-1.png");
			Moon::Texture* enemyTexture2 = new Moon::Texture("easy-enemy-2.png");
			Moon::Texture* enemyTexture3 = new Moon::Texture("easy-enemy-3.png");
			Moon::Material* enemyMaterial1 = new Moon::Material(Moon::MaterialType::Texture, enemyTexture1);
			Moon::Material* enemyMaterial2 = new Moon::Material(Moon::MaterialType::Texture, enemyTexture2);
			Moon::Material* enemyMaterial3 = new Moon::Material(Moon::MaterialType::Texture, enemyTexture3);
			enemyMaterials.push_back(enemyMaterial1);
			enemyMaterials.push_back(enemyMaterial2);
			enemyMaterials.push_back(enemyMaterial3);
		}
		else if (level == 2)
		{
			enemyHealth = 10;
			audioDuration = 7;
			backgroundTexture = new Moon::Texture("medium-background.png");
			Moon::Texture* enemyTexture1 = new Moon::Texture("medium-enemy-1.png");
			Moon::Texture* enemyTexture2 = new Moon::Texture("medium-enemy-2.png");
			Moon::Texture* enemyTexture3 = new Moon::Texture("medium-enemy-3.png");
			Moon::Material* enemyMaterial1 = new Moon::Material(Moon::MaterialType::Texture, enemyTexture1);
			Moon::Material* enemyMaterial2 = new Moon::Material(Moon::MaterialType::Texture, enemyTexture2);
			Moon::Material* enemyMaterial3 = new Moon::Material(Moon::MaterialType::Texture, enemyTexture3);
			enemyMaterials.push_back(enemyMaterial1);
			enemyMaterials.push_back(enemyMaterial2);
			enemyMaterials.push_back(enemyMaterial3);
		}
		else if (level == 3)
		{
			enemyHealth = 20;
			audioDuration = 17;
			backgroundTexture = new Moon::Texture("hard-background.png");
			Moon::Texture* enemyTexture = new Moon::Texture("hard-enemy-1.png");
			Moon::Material* enemyMaterial = new Moon::Material(Moon::MaterialType::Texture, enemyTexture);
			enemyMaterials.push_back(enemyMaterial);
		}

		backgroundMaterial = new Moon::Material(Moon::MaterialType::Texture, backgroundTexture);

		Vec3 backgroundPosition = Vec3(width / 2, height / 2, 0);
		Moon::Entity* background = new Moon::Entity(fixedRect, backgroundPosition, Vec3(), Vec3(width, height, 0));
		background->SetMaterial(backgroundMaterial);

		Vec3 playerPosition = Vec3(width / 2, 64 + 64 - 20, 0);
		player = new Moon::Entity(playerRect, playerPosition, Vec3(), Vec3(128, 128, 1));
		player->SetMaterial(playerMaterials[currPlayerMaterial]);

		Vec3 playerWeaponSize = Vec3();
		Vec3 playerWeaponPosition = Vec3(width / 2 + 60, 64 + 64 - 10, 0);
		playerWeapon = new Moon::Entity(fixedRect, playerWeaponPosition, Vec3(0, 0, 0), Vec3(64, 64, 1));
		playerWeapon->SetMaterial(currWeapon->Material);
		weaponHealth = currWeapon->Health;

		silverDiePosition = Vec3(width / 2 - 25 - 64 - 32 - 10, height - 50, 0);
		silverDie = new Moon::Entity(fixedRect, silverDiePosition, Vec3(), Vec3(64, 64, 1));
		silverDie->SetMaterial(silverDieMaterials[0]);

		goldDiePosition = Vec3(width / 2 - 25 - 32, height - 50, 0);
		goldDie = new Moon::Entity(fixedRect, goldDiePosition, Vec3(), Vec3(64, 64, 1));
		goldDie->SetMaterial(goldDieMaterials[0]);

		Int boulder1Width = boulderMaterials[0]->GetTexture()->GetWidth();
		Int boulder1Height = boulderMaterials[0]->GetTexture()->GetHeight();

		Vec3 boulder1Position = Vec3(-width + boulder1Width, height / 2 - 75, 0);
		Moon::Entity* boulder1 = new Moon::Entity(worldRect, boulder1Position, Vec3(), Vec3(boulder1Width, boulder1Height, 1));
		boulder1->SetMaterial(boulderMaterials[0]);

		Vec3 boulder2Position = Vec3(2 * width, height / 2, 0);
		Moon::Entity* boulder2 = new Moon::Entity(worldRect, boulder2Position, Vec3(), Vec3(boulderMaterials[1]->GetTexture()->GetWidth(), boulderMaterials[1]->GetTexture()->GetHeight(), 1));
		boulder2->SetMaterial(boulderMaterials[1]);

		Vec3 weaponPosition = Vec3(width / 2 + 25 + 32, height - 50, 0);
		weapon = new Moon::Entity(fixedRect, weaponPosition, Vec3(), Vec3(64, 64, 1));
		weapon->SetMaterial(currWeapon->Material);

		Vec3 healthPosition = Vec3(width - 100 - 20, height - 40, 0);
		health = new Moon::Entity(colorRect, healthPosition, Vec3(), Vec3(200, 40, 1));
		health->SetMaterial(new Moon::Material(Moon::MaterialType::Color, new Moon::Color(0, 255, 0)));

		Moon::Renderer::AddEntity(health);
		Moon::Renderer::AddEntity(player);
		Moon::Renderer::AddEntity(playerWeapon);
		Moon::Renderer::AddEntity(silverDie);
		Moon::Renderer::AddEntity(goldDie);
		Moon::Renderer::AddEntity(weapon);

		Moon::Renderer::AddEntity(boulder1);
		Moon::Renderer::AddEntity(boulder2);

		for (Int i = -2; i < 4; i++)
		{
			Vec3 groundPosition = Vec3((width + 2 * i * width) / 4, 32, 0);
			Moon::Entity* ground = new Moon::Entity(worldRect, groundPosition, Vec3(), Vec3(width / 2, 64, 1));
			ground->SetMaterial(groundMaterial);
			grounds.push_back(ground);
			Moon::Renderer::AddEntity(ground);
		}

		Moon::Renderer::AddEntity(background);

		Moon::CustomEvent* generateCloud = new Moon::CustomEvent(OnGenerateCloud, 6000, this);
		Moon::EventHandler::Push(generateCloud);

		PlayMusic();
		Moon::CustomEvent* loopMusic = new Moon::CustomEvent(OnPlayMusic, audioDuration * 1000, this);
		Moon::EventHandler::Push(loopMusic);

		SpawnEnemyCallback(this);
		Moon::CustomEvent* spawnEnemy = new Moon::CustomEvent(SpawnEnemyCallback, (4 - level) * 5000, this);
		Moon::EventHandler::Push(spawnEnemy);
	
		Moon::CustomEvent* collideCheck = new Moon::CustomEvent(CollideCheckCallback, 500, this);
		Moon::EventHandler::Push(collideCheck);
	}

	void GameOver()
	{
		gameOver = true;
		Int gameOverWidth = gameOverMaterial->GetTexture()->GetWidth() / 2;
		Int gameOverHeight = gameOverMaterial->GetTexture()->GetHeight() / 2;
		Moon::Entity* gameOverEntity = new Moon::Entity(gameOverRect, Vec3(width / 2, height / 2, 0), Vec3(), Vec3(gameOverWidth, gameOverHeight, 1));
		gameOverEntity->SetMaterial(gameOverMaterial);
		Moon::Renderer::AddEntity(gameOverEntity);
	}

	void OnCollideCheck()
	{
		for (const Moon::Entity* enemy : enemies)
		{
			if (std::abs(enemy->GetTranslation().x - (playerX + width)) < 20)
			{
				if (healthVal - 3 <= 0)
				{
					GameOver();
					return;
				}
				health->Scale(Vec3(-6, 0, 0));
				healthVal -= 3;
			}
		}
	}

	void SpawnEnemy()
	{
		if (gameOver) return;
		Vec3 enemyPosition = Vec3(Moon::Util::Random(-300, 1300), 64 + enemyMaterials[0]->GetTexture()->GetHeight() / 2 - 10, 0);
		Moon::Entity* enemy = new Moon::Entity(worldRect, enemyPosition, Vec3(), Vec3(enemyMaterials[0]->GetTexture()->GetWidth(), enemyMaterials[0]->GetTexture()->GetHeight(), 1));
		enemy->SetMaterial(enemyMaterials[0]);
		enemies.push_back(enemy);
		enemyHealths.push_back(enemyHealth);
		Moon::Renderer::AddEntity(enemy);
	}

	void StopFall()
	{
		jumpVelocity = 0;
		jumping = false;
	}

	void Fall()
	{
		jumpVelocity = -jumpSpeed;
		Moon::CustomEvent* stopFall = new Moon::CustomEvent(StopFallCallback, jumpTime, this, true);
		Moon::EventHandler::Push(stopFall);
	}

	void Click(Double x, Double y)
	{
		if (mainMenu)
		{
			for (Uint i = 0; i < 3; i++)
			{
				if (buttonHoverings[i])
				{
					level = i + 1;
					InitGame();
					return;
				}
			}
		}
		else
		{
			if (silverDieHovering && silverDieTimeout == 100)
			{
				Moon::CustomEvent* silverDieRoll = new Moon::CustomEvent(OnSilverDieRoll, silverDieTimeout, this, true);
				Moon::EventHandler::Push(silverDieRoll);
			}
			else if (goldDieHovering && goldDieTimeout == 100)
			{
				Moon::CustomEvent* goldDieRoll = new Moon::CustomEvent(OnGoldDieRoll, goldDieTimeout, this, true);
				Moon::EventHandler::Push(goldDieRoll);
			}
			else if (!weaponless)
			{
				attack = true;
				Int weaponX;
				if (playerFacingLeft)
				{
					weaponX = (playerX + width) - 100;
				}
				else
				{
					weaponX = (playerX + width) + 100;
				}
				for (Uint i = 0; i < enemies.size(); i++)
				{
					if (std::abs(enemies[i]->GetTranslation().x - weaponX) < 50)
					{
						weaponHealth--;
						if (weaponHealth <= 0)
						{
							weaponless = true;
						}
						enemyHealths[i] -= currWeapon->Damage;
						if (enemyHealths[i] <= 0)
						{
							Moon::Renderer::RemoveEntity(enemies[i]);
							enemies.erase(enemies.begin() + i);
							enemyHealths.erase(enemyHealths.begin() + i);
						}
					}
				}
			}
		}
	}

	void SilverDieRoll()
	{
		Int index = 0;
		do
		{
			index = Moon::Util::Random(0, 5);
		} while (index == currSilverDieMaterial);
		currSilverDieMaterial = index;
		silverDie->SetMaterial(silverDieMaterials[index]);
		silverDieTimeout *= 1.1;
		if (silverDieTimeout < 500)
		{
			Moon::CustomEvent* silverDieRoll = new Moon::CustomEvent(OnSilverDieRoll, silverDieTimeout, this, true);
			Moon::EventHandler::Push(silverDieRoll);
		}
		else
		{
			weaponless = false;
			currWeapon = weapons[index];
			weaponHealth = currWeapon->Health;
			weapon->SetMaterial(currWeapon->Material);
			playerWeapon->SetMaterial(currWeapon->Material);
			silverDieTimeout = 100;
		}
	}

	void GoldDieRoll()
	{
		Int index = 0;
		do
		{
			index = Moon::Util::Random(0, 5);
		} while (index == currGoldDieMaterial);
		currGoldDieMaterial = index;
		goldDie->SetMaterial(goldDieMaterials[index]);
		goldDieTimeout *= 1.1;
		if (goldDieTimeout < 500)
		{
			Moon::CustomEvent* goldDieRoll = new Moon::CustomEvent(OnGoldDieRoll, goldDieTimeout, this, true);
			Moon::EventHandler::Push(goldDieRoll);
		}
		else
		{
			freeze = true;
			Moon::CustomEvent* unfreeze = new Moon::CustomEvent(UnfreezeCallback, (index + 1) * 1000, this, true);
			Moon::EventHandler::Push(unfreeze);
			goldDieTimeout = 100;
		}
	}

	void OnUnfreeze()
	{
		freeze = false;
	}

	static void UnfreezeCallback(void* sb)
	{
		((Sandbox*)sb)->OnUnfreeze();
	}

	static void CollideCheckCallback(void* sb)
	{
		((Sandbox*)sb)->OnCollideCheck();
	}

	static void SpawnEnemyCallback(void* sb)
	{
		((Sandbox*)sb)->SpawnEnemy();
	}

	static void StopFallCallback(void* sb)
	{
		((Sandbox*)sb)->StopFall();
	}

	static void FallCallback(void* sb)
	{
		((Sandbox*)sb)->Fall();
	}

	static void OnSilverDieRoll(void* sb)
	{
		((Sandbox*)sb)->SilverDieRoll();
	}

	static void OnGoldDieRoll(void* sb)
	{
		((Sandbox*)sb)->GoldDieRoll();
	}

	static void ClickCallback(void* sb, Double x, Double y)
	{
		((Sandbox*)sb)->Click(x, y);
	}

	void MouseMove(Double x, Double y)
	{
		y = height - y;

		if (mainMenu)
		{
			for (Uint i = 0; i < buttons.size(); i++)
			{
				if (x > buttonPositions[i].x - 64 && x < buttonPositions[i].x + 64 && y > buttonPositions[i].y - 32 && y < buttonPositions[i].y + 32)
				{
					if (!buttonHoverings[i])
					{
						buttons[i]->Scale(Vec3(6));
					}
					buttonHoverings[i] = true;
				}
				else if (buttonHoverings[i])
				{
					buttons[i]->Scale(Vec3(-6));
					buttonHoverings[i] = false;
				}
			}
		}
		else
		{
			if (x > silverDiePosition.x - 32 && x < silverDiePosition.x + 32 && y > silverDiePosition.y - 32 && y < silverDiePosition.y + 32)
			{
				if (!silverDieHovering)
				{
					silverDie->Scale(Vec3(6));
					Moon::Window::SetCursorType(Moon::CursorType::Pointer);
				}
				silverDieHovering = true;
			}
			else if (silverDieHovering)
			{
				silverDie->Scale(-Vec3(6));
				Moon::Window::SetCursorType(Moon::CursorType::Normal);
				silverDieHovering = false;
			}

			if (x > goldDiePosition.x - 32 && x < goldDiePosition.x + 32 && y > goldDiePosition.y - 32 && y < goldDiePosition.y + 32)
			{
				if (!goldDieHovering)
				{
					goldDie->Scale(Vec3(6));
					Moon::Window::SetCursorType(Moon::CursorType::Pointer);
				}
				goldDieHovering = true;
			}
			else if (goldDieHovering)
			{
				goldDie->Scale(-Vec3(6));
				Moon::Window::SetCursorType(Moon::CursorType::Normal);
				goldDieHovering = false;
			}
		}
	}

	static void MouseMoveCallback(void* sb, Double x, Double y)
	{
		((Sandbox*)sb)->MouseMove(x, y);
	}

	void PlayMusic()
	{
		if (level == 1)
		{
			Moon::Audio::Play("Easy.wav");
		}
		else if (level == 2)
		{
			Moon::Audio::Play("Medium.wav");
		}
		else if (level == 3)
		{
			Moon::Audio::Play("Hard.wav");
		}
	}

	static void OnPlayMusic(void* sb)
	{
		Sandbox* sandbox = (Sandbox*)sb;
		sandbox->PlayMusic();
	}

	void GenerateCloud()
	{
		Int cloudNo = Moon::Util::Random(0, 7);
		Moon::Material* cloudMaterial = cloudMaterials[cloudNo];
		Int cloudWidth = cloudMaterial->GetTexture()->GetWidth() / 2;
		Int cloudHeight = cloudMaterial->GetTexture()->GetHeight() / 2;
		Moon::Entity* cloud = new Moon::Entity(fixedRect, Vec3(width + cloudWidth / 2, height - 50 - Moon::Util::Random(0, 200), 0), Vec3(), Vec3(cloudWidth, cloudHeight, 1));
		cloud->SetMaterial(cloudMaterial);
		Moon::Renderer::AddEntity(cloud);
		clouds.push_back(cloud);
	}

	static void OnGenerateCloud(void* sb)
	{
		Sandbox* sandbox = (Sandbox*)sb;
		sandbox->GenerateCloud();
	}
private:
	Bool weaponless;
	Bool freeze;
	Bool gameOver;
	Bool jumping;
	Bool mainMenu;
	Bool oneDown;
	Bool twoDown;
	Bool playerFacingLeft;
	Bool attack;
	Uint enemyHealth;
	Uint level;
	Uint jumpTime;
	Uint audioDuration;
	Uint currWeaponIndex;
	Uint currPlayerMaterial;
	Uint currSilverDieMaterial;
	Uint currGoldDieMaterial;
	Uint currPlayerAnimationFrame;
	Double healthVal;
	Double silverDieTimeout;
	Double goldDieTimeout;
	Double jumpVelocity;
	Float jumpSpeed;
	Float playerWeaponX;
	Float playerSpeed;
	Float playerX;
	Float playerHealth;
	Float weaponHealth;
	Vec3 silverDiePosition;
	Vec3 goldDiePosition;
	Bool silverDieHovering;
	Bool goldDieHovering;
	Weapon* currWeapon;
	Moon::Camera* camera;
	Moon::Shader* gameOverShader;
	Moon::Shader* fixedShader;
	Moon::Shader* colorShader;
	Moon::Shader* playerShader;
	Moon::Shader* worldShader;
	Moon::Entity* health;
	Moon::Entity* logo;
	Moon::Entity* silverDie;
	Moon::Entity* goldDie;
	Moon::Entity* weapon;
	Moon::Entity* player;
	Moon::Entity* playerWeapon;
	Moon::Material* backgroundMaterial;
	Moon::Material* gameOverMaterial;
	Moon::Material* logoMaterial;
	Moon::Material* groundMaterial;
	Moon::Model* gameOverRect;
	Moon::Model* fixedRect;
	Moon::Model* colorRect;
	Moon::Model* playerRect;
	Moon::Model* worldRect;
	List<Int> enemyHealths;
	List<Uint> weaponDamages;
	List<Vec3> buttonPositions;
	List<Bool> buttonHoverings;
	List<Weapon*> weapons;
	List<Moon::Entity*> buttons;
	List<Moon::Entity*> clouds;
	List<Moon::Entity*> grounds;
	List<Moon::Entity*> enemies;
	List<Moon::Material*> enemyMaterials;
	List<Moon::Material*> boulderMaterials;
	List<Moon::Material*> playerMaterials;
	List<Moon::Material*> buttonMaterials;
	List<Moon::Material*> cloudMaterials;
	List<Moon::Material*> silverDieMaterials;
	List<Moon::Material*> goldDieMaterials;
	List<Moon::Material*> weaponMaterials;
	static const Int width = 860;
	static const Int height = 480;
	static const Int leftBorder = -1190;
	static const Int rightBorder = 505;
};

Moon::Application* Moon::CreateApplication()
{
	return new Sandbox();
}