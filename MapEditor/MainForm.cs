//  ------------------------------------------------------------------------------
// 
//  GoldenSaber
//     Copyright 2023 Matthew Rogers
// 
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
// 
//         http://www.apache.org/licenses/LICENSE-2.0
// 
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
// 
//  File Name: MainForm.cs
//  Date File Created: 12/09/2023
//  Author: Matt
// 
//  ------------------------------------------------------------------------------

using System.Drawing;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class MainForm : Form
    {

        private const int TileSize = 16;
        private const int GridSize = 32;
        private int[,] TileMap = new int[GridSize, GridSize];
        private MenuStrip menuStrip1;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem saveToolStripMenuItem;
        private ToolStripMenuItem openToolStripMenuItem;
        private PictureBox pictureBox1;
        private System.ComponentModel.IContainer components = null;

        private Bitmap spritesheet;

        private int selected_tile_index = 0;

        public MainForm()
        {
            InitializeComponent();
            InitializeTileMap();
            spritesheet = new Bitmap("../../../GoldenSaber/assets/sprites/basictiles.png");
            pictureBox1.Image = spritesheet;
        }

        private void InitializeTileMap()
        {
            for (var x = 0; x < GridSize; x++)
            {
                for (var y = 0; y < GridSize; y++)
                {
                    TileMap[x, y] = -1;
                }
            }
        }

        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1267, 33);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveToolStripMenuItem,
            this.openToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(54, 29);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(158, 34);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(158, 34);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(1004, 460);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(251, 314);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1267, 827);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Map Editor";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.MainForm_Paint);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.MainForm_MouseClick);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            DrawGrid(e.Graphics);
            DrawTiles(e.Graphics);
        }

        private void DrawTiles(Graphics g)
        {
            for (var i = 0; i < GridSize; i++)
            {
                for (var j = 0; j < GridSize; j++)
                {
                    var spriteIndex = TileMap[i, j];
                    if (TileMap[i, j] == -1) continue;
                    // TODO: Draw the tile
                    //Brush brush = new SolidBrush(Color.Blue);
                    //g.FillRectangle(brush, i * TileSize, j * TileSize, TileSize, TileSize);
                    int row = spriteIndex / (spritesheet.Width / TileSize);
                    int col = spriteIndex % (spritesheet.Width / TileSize);
                    Rectangle srcRect = new Rectangle(col * TileSize, row * TileSize, TileSize, TileSize);
                    g.DrawImage(spritesheet, new Rectangle(i * TileSize, j * TileSize, TileSize, TileSize), srcRect, GraphicsUnit.Pixel);
                }
            }
        }

        private void MainForm_MouseClick(object sender, MouseEventArgs e)
        {
            var x = e.X / TileSize;
            var y = e.Y / TileSize;
            if (x < 0 || x >= GridSize || y < 0 || y >= GridSize) return;
            TileMap[x, y] = selected_tile_index;

            int row = TileMap[x, y] / (spritesheet.Width / TileSize);
            int col = TileMap[x, y] % (spritesheet.Width / TileSize);
            //Rectangle sourceRect = new Rectangle(col * TileSize, row * TileSize, TileSize, TileSize);
            //pictureBox1.Image = new Bitmap(spritesheet.Clone(sourceRect, spritesheet.PixelFormat));

            Invalidate();
        }

        private void DrawGrid(Graphics g)
        {
            Pen pen = new Pen(Color.Black);
            for (var i = 0; i < GridSize; i++)
            {
                g.DrawLine(pen, i * TileSize, 0, i * TileSize, GridSize * TileSize);
                g.DrawLine(pen, 0, i * TileSize, GridSize * TileSize, i * TileSize);
            }
        }

        private void saveToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Text files|*.txt";

            if (saveFileDialog.ShowDialog() != DialogResult.OK) return;
            using (var sw = new System.IO.StreamWriter(saveFileDialog.FileName))
            {
                for (var i = 0; i < GridSize; i++)
                {
                    for (var j = 0; j < GridSize; j++)
                    {
                        sw.Write(TileMap[i, j] + " ");
                    }
                    sw.WriteLine();
                }
            }
        }

        private void openToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Text files|*.txt";

            if (openFileDialog.ShowDialog() != DialogResult.OK) return;
            InitializeTileMap(); // Clear existing tile map

            using (var sr = new System.IO.StreamReader(openFileDialog.FileName))
            {
                for (var i = 0; i < GridSize; i++)
                {
                    var values = sr.ReadLine()?.Split(' ');
                    for (var j = 0; j < GridSize; j++)
                    {
                        if (values != null) TileMap[i, j] = int.Parse(values[j]);
                    }
                }
            }

            Invalidate();
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            //var x = e.X / TileSize;
            //var y = e.Y / TileSize;
            //TileMap[x, y] = 0;

            //int row = TileMap[x, y] / (spritesheet.Width / TileSize);
            //int col = TileMap[x, y] % (spritesheet.Width / TileSize);
            //Rectangle sourceRect = new Rectangle(col * TileSize, row * TileSize, TileSize, TileSize);
            //pictureBox1.Image = new Bitmap(spritesheet.Clone(sourceRect, spritesheet.PixelFormat));

            //Invalidate();

            selected_tile_index = GetTileIndexFromMouseClick(e);
        }

        private int GetTileIndexFromMouseClick(MouseEventArgs e)
        {
            var x = e.X / TileSize;
            var y = e.Y / TileSize;
            return y * (spritesheet.Width / TileSize) + x;
        }
    }
}