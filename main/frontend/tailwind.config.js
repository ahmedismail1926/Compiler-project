/** @type {import('tailwindcss').Config} */
export default {
  content: ["./index.html", "./src/**/*.{js,ts,jsx,tsx}"],
  theme: {
    extend: {
      colors: {
        "dark-bg": "#1e1e1e",
        "dark-surface": "#252526",
        "dark-border": "#3c3c3c",
        accent: "#007acc",
        "accent-hover": "#1e90ff",
        error: "#f44747",
        success: "#4ec9b0",
        warning: "#dcdcaa",
      },
    },
  },
  plugins: [],
};
