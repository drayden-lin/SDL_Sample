#include "Include/ViewPort.h"

	int ViewPort::Main() {
		if (!init())return -1;
		//if (!loadMedia(" 32 "))return -1;

		SDL_Event ev;
		bool quit = false;

		//Set up viewports
		//SDL_Rect topLeftViewport = {0, 0, screenWidth/2, screenHeight/2};
		//SDL_Rect topRightViewport = { screenWidth / 2, 0, screenWidth / 2, screenHeight / 2 };
		//SDL_Rect bottomViewport = { 0, screenHeight / 2 , screenWidth,  screenHeight / 2 };
		setUpViewports();
		setUpNum();
		//setUpTexture();
		bool once = false;
		int curr = 1;
		int input = 0;

		while (!quit) {
			while (SDL_PollEvent(&ev) != 0) {
				if (curr > 32)
					quit = true;
				if (ev.type == SDL_QUIT) {
					quit = true;
				}
				else if (ev.type == SDL_KEYDOWN) {
					//Select surfaces based on key press
					switch (ev.key.keysym.sym)
					{
					case SDLK_e:
						input = 0;
						if (solution[curr] == input) {
							printf("Correct! Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
							setDefaultTexture(curr, input);
							curr++;
						}
						else
							printf("Incorrect!Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
						break;
					case SDLK_r:
						input = 1;
						if (solution[curr] == input) {
							printf("Correct! Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
							setDefaultTexture(curr, input);
							curr++;
						}
						else
							printf("Incorrect!Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
						break;
					case SDLK_d:
						input = 2;
						if (solution[curr] == input) {
							printf("Correct! Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
							setDefaultTexture(curr, input);
							curr++;
						}
						else
							printf("Incorrect!Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
						break;
					case SDLK_f:
						input = 3;
						if (solution[curr] == input) {
							printf("Correct! Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
							setDefaultTexture(curr, input);
							curr++;
						}
						else
							printf("Incorrect!Number: %d, Input: %d, Location: %d\n", curr, input, solution[curr]);
						break;
					default:
						printf("default\n");
					}
				}
			}
			if (!once) {
				SDL_SetRenderDrawColor(vpRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(vpRenderer);

				//for each viewport, we do setViewport and RenderCopy

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 2; k++) {
							SDL_RenderSetViewport(vpRenderer, &(viewports[i][j][k].location));
							loadMedia((viewports[i][j][k].num));
							//vpTexture = viewports[i][j][k].txt;
							SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);
						}
					}
				}
				once = true;
				/*SDL_RenderSetViewport(vpRenderer, &topLeftViewport);
				SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);

				SDL_RenderSetViewport(vpRenderer, &topRightViewport);
				SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);
				SDL_RenderSetViewport(vpRenderer, &bottomViewport);
				SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);*/

				//When all done, we present
				SDL_RenderPresent(vpRenderer);
			}
		}
		close();
		while (1);
		return 0;
	}

	bool ViewPort::init() {
		if (SDL_Init(SDL_INIT_VIDEO)<0) {
			return false;
		}

		if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)) {
			return false;
		}

		vpWindow = SDL_CreateWindow("SDL_Sample_Viewport", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (!vpWindow) {
			return false;
		}
		vpWindowSurface = SDL_GetWindowSurface(vpWindow);
		if (!vpWindowSurface) {
			return false;
		}

		vpRenderer = SDL_CreateRenderer(vpWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!vpRenderer) {
			return false;
		}
		if (TTF_Init() == -1) {
				printf("TTF_Init() Failed\n");
				return false;
			}
		srand(SDL_GetTicks());
		for (int i = 0; i < 32; i++) {
			solution[i] = 0;
		}
		//setCheck.clear();
		return true;

	}

	bool ViewPort::loadMedia(int index) {

		SDL_Surface* tempSurface = NULL;
		SDL_Color textColor = { 0, 0, 0 };

		switch (index)
		{
		case 1:
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/1.png"));break;
		case 2:
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/2.png")); break;
		case 3:
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/3.png")); break;
		case 4:
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/4.png")); break;
		case 5:																	
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/5.png")); break;
		case 6:																	
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/6.png")); break;
		case 7:																	
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/7.png")); break;
		case 8:																	
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/8.png")); break;
		case 9:																	
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/9.png")); break;
		case 10:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/10.png")); break;
		case 11:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/11.png")); break;
		case 12:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/12.png")); break;
		case 13:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/13.png")); break;
		case 14:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/14.png")); break;
		case 15:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/15.png")); break;
		case 16:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/16.png")); break;
		case 17:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/17.png")); break;
		case 18:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/18.png")); break;
		case 19:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/19.png")); break;
		case 20:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/20.png")); break;
		case 21:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/21.png")); break;
		case 22:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/22.png")); break;
		case 23:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/23.png")); break;
		case 24:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/24.png")); break;
		case 25:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/25.png")); break;
		case 26:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/26.png")); break;
		case 27:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/27.png")); break;
		case 28:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/28.png")); break;
		case 29:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/29.png")); break;
		case 30:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/30.png")); break;
		case 31:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/31.png")); break;
		case 32:																
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/32.png")); break;
		default:
			vpTexture = SDL_CreateTextureFromSurface(vpRenderer, IMG_Load("Data/digitCancelling/default.png"));
			break;
		}
			
		if (!vpTexture) {
			SDL_FreeSurface(tempSurface);
			printf("texture is null\n");
			return false;
		}
		SDL_FreeSurface(tempSurface);
		return true;
	}

	void ViewPort::close() {

		SDL_DestroyRenderer(vpRenderer);
		SDL_DestroyTexture(vpTexture);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	void ViewPort::setUpViewports() {
		//SDL_Rect bottomViewport = { 0, screenHeight / 2 , screenWidth,  screenHeight / 2 };
		// TOP LEFT
		viewports[0][0][0].location = {   0,   0, 100, 150 };
		viewports[0][1][0].location = { 100,   0, 100, 150 };
		viewports[0][2][0].location = { 200,   0, 100, 150 };
		viewports[0][3][0].location = { 300,   0, 100, 150 };

		viewports[0][0][1].location = {   0, 150, 100, 150 };
		viewports[0][1][1].location = { 100, 150, 100, 150 };
		viewports[0][2][1].location = { 200, 150, 100, 150 };
		viewports[0][3][1].location = { 300, 150, 100, 150 };

		// TOP RIGHT
		viewports[1][0][0].location = { 400,   0, 100, 150 };
		viewports[1][1][0].location = { 500,   0, 100, 150 };
		viewports[1][2][0].location = { 600,   0, 100, 150 };
		viewports[1][3][0].location = { 700,   0, 100, 150 };

		viewports[1][0][1].location = { 400, 150, 100, 150 };
		viewports[1][1][1].location = { 500, 150, 100, 150 };
		viewports[1][2][1].location = { 600, 150, 100, 150 };
		viewports[1][3][1].location = { 700, 150, 100, 150 };

		// BOTTOM LEFT
		viewports[2][0][0].location = {   0, 300, 100, 150 };
		viewports[2][1][0].location = { 100, 300, 100, 150 };
		viewports[2][2][0].location = { 200, 300, 100, 150 };
		viewports[2][3][0].location = { 300, 300, 100, 150 };

		viewports[2][0][1].location = {   0, 450, 100, 150 };
		viewports[2][1][1].location = { 100, 450, 100, 150 };
		viewports[2][2][1].location = { 200, 450, 100, 150 };
		viewports[2][3][1].location = { 300, 450, 100, 150 };

		// BOTTOM RIGHT
		viewports[3][0][0].location = { 400, 300, 100, 150 };
		viewports[3][1][0].location = { 500, 300, 100, 150 };
		viewports[3][2][0].location = { 600, 300, 100, 150 };
		viewports[3][3][0].location = { 700, 300, 100, 150 };

		viewports[3][0][1].location = { 400, 450, 100, 150 };
		viewports[3][1][1].location = { 500, 450, 100, 150 };
		viewports[3][2][1].location = { 600, 450, 100, 150 };
		viewports[3][3][1].location = { 700, 450, 100, 150 };

	}
	int ViewPort::getRand() {
		return (rand() % 32) + 1;
	}
	void ViewPort::setUpNum() {
		// TOP LEFT
		std::set<int> setCheck;
		int temp = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 2; k++) {
					temp = getRand();
					bool isOkay = false;
					std::pair<std::set<int>::iterator, bool> iter;
					while (!isOkay) {
						iter = setCheck.insert(temp);
						if (!iter.second)
							temp = getRand();
						else
							isOkay = true;
					}
					//temp = getUniqueNum();
					viewports[i][j][k].num = temp;
					solution[temp] = i;
				}
			}
		}
	}

	int ViewPort::getUniqueNum() {
		int temp = getRand();
		for(int i =1; i<33; i++){
			//setCheck.insert(i);

		//if(setCheck.empty()){
		//	setCheck.insert(temp);
		//	return temp;
		//}
		//else {
		//	bool isOkay = false;
		//	while (!isOkay) {
		//std::set<int>::iterator iter = setCheck.find(temp);
		////std::set<int>::iterator iter2 = setCheck.end();
		//		if (1) {
		//		printf("okay");
		//		//if (setCheck.count(temp) == 0) {
		//			isOkay = true;
		//		}
		//		else {
		//			temp = getRand();
		//		}
		//	}
		//	setCheck.insert(temp);
			return temp;

		}
	}

	void ViewPort::setDefaultTexture(int curr, int quad) {

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				if (viewports[quad][i][j].num == curr) {
					SDL_RenderSetViewport(vpRenderer, &(viewports[quad][i][j].location));
					loadMedia(0);
					//vpTexture = viewports[i][j][k].txt;
					SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);
					SDL_RenderPresent(vpRenderer);
				}


			}
		}

	}