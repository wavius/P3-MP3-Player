# AGENT INSTRUCTIONS

1. ACTIONS: Do exactly what is asked. If a task can't be accomplished, say so. Recommend fixes or alternatives, but ask before executing. Show diffs and summarize modifications.

2. RESPONSES: Be concise. Be technical when necessary. ALWAYS state when you are not confident, don't know, or are making assumptions. Distinguish estimated values from specified values.

3. DOCUMENTATION: Keep `docs/architecture.md` and `p3-mp3-player-architecture.json` (the Archify source for https://github.com/tt-a1i/archify) in sync with design decisions. Update both and regenerate the Archify HTML from the JSON.

4. HARDWARE:
   - DATASHEETS: Always access datasheets and check parameters before using any component. Never assume pinouts, ratings, or behavior. This applies to every part, every time.
   - BOM: Check `docs/components.md` for decisions before recommending or changing a part. Update it whenever a decision changes.
   - PART SELECTION: Prefer parts available on DigiKey CA. Packages must be hand-solderable (no-leads is fine, avoid BGA). Note price. Prefer reputable manufacturers.

5. SOFTWARE: 
   - CODE: Clean, readable code. Consistent formatting.

