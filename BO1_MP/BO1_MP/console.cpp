#include <devstation\System.h>
#include <devstation\Math.h>
#include <devstation\Vector.h>

#include <Structures.h>
#include <functions.h>
#include <console.h>
#include <menu.h>


Console console;



void Console::draw()
{
	float x, w, ys, h; x = 14; ys = 625; w = 380; h = 360;//stack
	float start_w = 20, start_h = 20;
	//DrawStaticOutline(x, ys, w, h, menu.skin, 2.1);//outline
	//DrawShaderUI(x, ys, w, h, 0, color(0, 0, 0, 200), "white", 0, align_left);//back
	for (int i = 0; i < CONSOLE_MAX_ITEMS; i++)
	{
		consoleitem item = this->items[i];
		if (*item.text == 0) continue;

		if (this->items[i].colour.a > 0)
		{
			//DrawTextWithBackground_UI(item.text, x + 5, ys + (local->consoley[i]), .93, item.colour, menu.skin, item.color1, align_left);

			String pszfont = R_GetFontPathFromName("extraSmallFont");
			//int text_w = R_TextWidth(item.text, pszfont, 0.93 * 1.3) + start_w;
			int text_h = R_TextHeight(pszfont, 0.93) + start_h;

			//DrawStaticOutline(x, ys + (local->consoley[i] + 10), text_w, text_h, item.color2, item.color3, 2.1);
			//DrawShaderUI(x, ys + (local->consoley[i] + 10), text_w, text_h, 0, item.color1, "white", 7, align_left);

			DrawTextUI(item.text, x + (start_w / 2), ys + (local->consoley[i] + 10) - (start_h / 4) + text_h + 2, 0, 0.93, "extraSmallFont", item.colour, align_left);
		}

		if (this->items[i].time > 0)
			this->items[i].time--;

		if (this->items[i].time <= 0) {
			this->items[i].colour.a -= 0.001;
			this->items[i].color1.a -= 0.001;
			this->items[i].color2.a -= 0.001;
			this->items[i].color3.a -= 0.001;
			if (this->items[i].colour.a <= 0)
				this->arrange(i);
		}
	}
}

void Console::write(const char * text, color && colour, color && colour1, color && colour2, color && colour3)
{
	this->arrange(CONSOLE_DEFAULT_ITEM);
	strcpy(this->items[CONSOLE_DEFAULT_ITEM].text, text);
	this->items[CONSOLE_DEFAULT_ITEM].colour = colour;
	this->items[CONSOLE_DEFAULT_ITEM].color1 = colour1;
	this->items[CONSOLE_DEFAULT_ITEM].color2 = colour2;
	this->items[CONSOLE_DEFAULT_ITEM].color2 = colour3;
	this->items[CONSOLE_DEFAULT_ITEM].time = 255;
}

void Console::arrange(int index)
{
	consoleitem temp[CONSOLE_MAX_ITEMS];// = consoleitem();
	for (uint32_t i = 0, spot = 0; i < CONSOLE_MAX_ITEMS; i++)
	{
		if (i == index)
			continue;
		else
			temp[i] = items[spot++];
	}
	for (int i = 0; i < CONSOLE_MAX_ITEMS; i++)
		items[i] = temp[i];
}

consoleitem * Console::getItem(int column)
{
	if (column > CONSOLE_MAX_ITEMS)
		return nullptr;
	return &this->items[column];
}

bool Console::contains(const char * string)
{
	for (int i = 0; i < CONSOLE_MAX_ITEMS; i++)
	{

	}
	return false;
}

bool Console::isfilled()
{
	return (*this->items[0].text != 0) && (*this->items[1].text != 0) && (*this->items[2].text != 0)
		&& (*this->items[3].text != 0) && (*this->items[4].text != 0) && (*this->items[5].text != 0);
}

void Console::clear()
{
	for (int i = 0; i < CONSOLE_MAX_ITEMS; i++)
		this->items[i] = consoleitem();				/// set to default console item
}