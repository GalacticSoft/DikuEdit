# ![Alt text](http://i.imgur.com/3ZGERJM.png)
Azmyth is a generic game framework used to create flexible RPG and adventure style games using procedural content generation.  
	
#### Features include:
- Extensible Asset system.
- Perlin Noise, Simplex Noise, Random Noise
- Terrain generation using Perlin Noise and QuadTrees.
- Flexible Stat/Attribute system.
- Markov Chain name/text generator.
- Chunk loading.

#### Planned Features:
- Biomes.
- Procedurally generated Cities and Economic simulation.
- Races and Classes.
- Additional Noise generators (Worley/Voronoi, Wavelet, etc).
- Procedurally generated NPCS, Items, Quests.
- Dynamic Chunk Loading.

#### Code Samples

- Creating a World and Loading Chunks

		//Create World with random seed
		World world = new World(12345);
		
		//Set parameters
		world.CoastLine = 0.00f;  //Coast starts at height 0
		world.ShoreLine = 0.05f;  //Shore line is 5% higher than coast line
		world.TreeLine  = 0.40f;  //Tree line is 40% higher than coast line
		world.SnowLine  = 0.50f;  //Snow line is 50% higher than coast line
		
		//Load 50x50 chunk at tile 0, 0
		TerrainChunk chunk = world.LoadChunk(new RectangleF(0, 0, 50, 50));
		
		//Load 10x10 chunk at tile 5, 6
		TerrainChunk chunk2 = world.LoadChunk(new RectangleF(5, 6, 10, 10));
		
		//Load 100x100 chunk at tile 0, 0
		TerrainChunk chunk3 = world.LoadChunk(new RectangleF(100, 100, 100, 100));

- Chunk Loading

		/// <summary>
		/// Loads tiles from world that are contained within chunkBounds
		/// </summary>
		/// <param name="world"></param>
		/// <param name="chunkBounds"></param>
		public TerrainChunk(World world, RectangleF chunkBounds) : this()
		{
		    //Calculate total tiles in chunk
		    int totalTiles = (int)chunkBounds.Width * (int)chunkBounds.Height;
		
		    //Loop through each tile
		    for (int index = 0; index < totalTiles; index++)
		    {
		        //Convert index value into x and y coordinates.
		        int cellX = (int)((index / chunkBounds.Height)) + (int)chunkBounds.X;
		        int cellY = (int)((index % chunkBounds.Height)) + (int)chunkBounds.Y;
		
		        //Load tile.
		        TerrainTile tile = world.LoadTile(cellX, cellY, this);
		
		        //Insert new tile into chunk QuadTree
		        m_tiles.Insert(tile);
		     }
		
		     //Assign local variables
		     m_world = world;
		     m_bounds = chunkBounds;
		}

- Chunk Rendering

		/// <summary>
		/// Draws the loaded chunks visible in the viewport
		/// </summary>
		public void Draw()
		{
		    //Convert the viewport rectangle into tiles
		    RectangleF viewportRect = ScreenToTile(new Rectangle(Viewport.X, 
		        Viewport.Y, Viewport.Width, Viewport.Height));
		 
		    //Load only the chunks visible in the viewport. (Includes partial chunks)
		    List<TerrainChunk> chunks = m_world.GetChunks(viewportRect);
		
		    m_spriteBatch.Begin(SpriteSortMode.Deferred, 
		        null, null, null, null, null, Matrix.CreateTranslation(0, 0, 0));
		
		    //Loop through each visible chunk.
		    foreach (TerrainChunk chunk in chunks)
		    {
		        //Load only tiles visible in the viewport. (Includes partial tiles)
		        List<TerrainTile> tiles = chunk.GetTiles(viewportRect);
		
		        //Loop through each visible tile.
		        foreach (TerrainTile t in tiles)
		        {
		            //Draw tile to screen.
		            m_spriteBatch.Draw(m_cellTextures[t.Terrain], 
		                TileToScreen(t.Bounds), Color.White);
		
		            //Add any additional rendering for tiles here.
		        }
		
		        // Add any additional rendering for chunks here.
		    }
		
		    m_spriteBatch.End();
		}

#### XNA
- Intro
![ScreenShot](http://i.imgur.com/4jJVU4e.png)
![ScreenShot](http://i.imgur.com/kjeI0zo.png)

- Chunk Loading
![ScreenShot](http://i.imgur.com/dXJ3UPk.png)
![ScreenShot](http://i.imgur.com/nkxVyAN.png)

- Mini Map
![ScreenShot](http://i.imgur.com/9FyRYfY.png)
![ScreenShot](http://i.imgur.com/zuaQza5.png)

#### GDI
- Terrain Map
![ScreenShot](http://i.imgur.com/V0Nfvx6.png)

- Height Map
![ScreenShot](http://i.imgur.com/9lYTbOv.png)

- Temperature Map
![ScreenShot](http://i.imgur.com/PQq61hR.png)

#### License & Copyright

Copyright (c) 2014 Marissa du Bois

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

#### Author
<p>
<table width="100%" cellpadding="0" cellspacing="0">
<tr  width="100%" height="211px" cellpadding="0" cellspacing="0">
<td cellpadding="0" cellspacing="0" height="211px" width="135px"><center><img src="http://i.imgur.com/H98nfdu.jpg"  /></center></td>
<td >
<strong>Marissa Willow du Bois</strong>
<br>
Marissa is an avid programmer and has been developing software for the past sixteen years. She is currently employed as a programmer analyst developing accounting software for the wine industry.
<br>
<br>
<strong>Contact:</strong> marissa@galacticsoft.net
<br>
<strong>Website:</strong> http://www.galacticsoft.net
</td>
</tr>
</table>
<p>
