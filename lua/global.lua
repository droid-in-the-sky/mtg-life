UI_ALIGN = {    -- TODO other file
    left   = 0,     top    = 0,
    center = 1,     middle = 1,
    right  = 2,     bottom = 2,
}

local CLR = {
    brown = { 0x40, 0x0D, 0x12 },
}

local DIR
if UI_H < 400 then
    DIR = 'imgs/low'
elseif UI_H < 800 then
    DIR = 'imgs/medium'
else
    DIR = 'imgs/medium'
end

grid_main = {
    --clr_bg = CLR.lightgrey,
    lay = {
        lins = 7,
        cols = 1,
        1, 2, 2, 2, 2, 2, 2
    },
    uis = {
        {   -- BAR
            clr_bg = CLR.brown,
            lay = {
                lins = 1,
                cols = 6,
                1, 2, 3, 4, 0, 0, 0  -- new,pls,snd,dice
            },
            uis = {
                { img=DIR..'/new.png' },
                { img=DIR..'/players.png' },
                { img=DIR..'/mute.png' },
                { img=DIR..'/dice.png' },
            },
        },
        {   -- PLAYERS
            lay = {
                lins = 2,
                cols = 2,
                1, 2, 3, 4
            },
            uis = { {}, {}, {}, {} }
        },
    },
}

grid_counter = {
    pad_x = 1/50,
    pad_y = 1/50,
    lay = {
        lins = 3,
        cols = 3,
        0, 1, 0,    -- inc
        0, 2, 0,    -- cnt
        0, 3, 4,    -- dec, hist
    },
    uis = {
        { img=DIR..'/inc.png' },
        { },        -- cnt
        { img=DIR..'/dec.png' },
        { },        -- hist
    },
}
