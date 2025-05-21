return {
  {
    'sainnhe/gruvbox-material',
    priority = 1000,
    config = function()
      -- Set background before loading the theme
      vim.o.background = 'dark' -- or "light" if you prefer

      -- Recommended settings for gruvbox-material
      vim.g.gruvbox_material_background = 'medium' -- "soft", "medium", or "hard"
      vim.g.gruvbox_material_enable_italic = 0
      vim.g.gruvbox_material_transparent_background = 1

      -- Apply the colorscheme
      vim.cmd 'colorscheme gruvbox-material'
      vim.cmd [[
  highlight NormalFloat guibg=NONE
  highlight FloatBorder guibg=NONE
  highlight Normal guibg=NONE
  highlight SignColumn guibg=NONE
  highlight VertSplit guibg=NONE
]]
    end,
  },
}
