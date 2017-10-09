class Application {

    constructor(canvas_id, pointer_id, target_id) {
        this.canvas_id = canvas_id;
        this.pointer_id = pointer_id;
        this.target_id = target_id;
        this.canvas = null;
        this.pointer = null;
    }
    
    load_app() {
        this.canvas = document.getElementById(this.canvas_id);
        this.pointer = document.getElementById(this.pointer_id);
        var ctx = this.canvas.getContext('2d');
        ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }

    draw_networkMap(matrix) {
        let width = this.canvas.width;
        let height = this.canvas.height;

        let row_height = height / 100;
        let col_width = width / 100;
        var ctx = this.canvas.getContext('2d');

        for(let i = 0; i < matrix.length; i++) {
            for(let j = 0; j < matrix[i].length; j++) {
                if (matrix[i][j] == 1) {
					ctx.beginPath();
                    ctx.arc(j * col_width, i * row_height, 8, 0, 2*Math.PI);
					ctx.fillStyle = "blue";
					ctx.fill();
					ctx.stroke();
                }
            }
        }
    }

    begin() {
        var ctx = this.canvas.getContext('2d');
        ctx.beginPath();
    }

    finish() {
        var ctx = this.canvas.getContext('2d');
        ctx.stroke();
    } 
}