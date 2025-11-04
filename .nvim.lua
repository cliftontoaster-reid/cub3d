-- Project-specific Neovim configuration
-- Use Python command for C/H file formatting instead of clang-format

-- Configure conform.nvim to use a custom Python formatter
local conform = require("conform")

-- Register a custom formatter that uses your Python command
conform.formatters.python_c_formatter = {
	command = "python3",
	-- Replace this with the actual path to your Python script
	args = { "-m", "c_formatter_42", "$FILENAME" },
	stdin = false,
}

-- Set up formatters for C and H files
conform.setup({
	formatters_by_ft = {
		c = { "python_c_formatter" },
		h = { "python_c_formatter" },
	},
})

-- Optional: Auto-format on save for C and H files
vim.api.nvim_create_autocmd("BufWritePre", {
	pattern = { "*.c", "*.h" },
	callback = function(args)
		conform.format({ bufnr = args.buf })
	end,
})
